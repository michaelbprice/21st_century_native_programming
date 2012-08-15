#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <utility>

#include "Board.hpp"
#include "Logger.hpp"
#include "Stone.hpp"

using namespace std;

namespace Go {

Board::Board ()
  : m_ko({false, m_points[0][0]})
{
    LOGFUNCTION(cout, "Board::Board");

    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t column =0; column < BOARD_SIZE; ++column)
        {
            m_points[row][column].coordinates.row = row; 
            m_points[row][column].coordinates.column = column; 
        }
    }
}

const Point & Board::getPointAbove (const Point & point) const
{
    LOGFUNCTION(cout, "Board::getPointAbove");

    if (point.coordinates.row - 1 < BOARD_SIZE)
        return m_points[point.coordinates.row - 1][point.coordinates.column];

    return point;
}

const Point & Board::getPointBelow (const Point & point) const
{
    LOGFUNCTION(cout, "Board::getPointBelow");

    if (point.coordinates.row + 1 < BOARD_SIZE)
        return m_points[point.coordinates.row + 1][point.coordinates.column];

    return point;
}

const Point & Board::getPointLeft (const Point & point) const
{
    LOGFUNCTION(cout, "Board::getPointLeft");

    if (point.coordinates.column - 1 < BOARD_SIZE)
        return m_points[point.coordinates.row][point.coordinates.column - 1];

    return point;
}

const Point & Board::getPointRight (const Point & point) const
{
    LOGFUNCTION(cout, "Board::getPointRight");

    if (point.coordinates.column + 1 < BOARD_SIZE)
        return m_points[point.coordinates.row][point.coordinates.column + 1];

    return point;
}

Stone::Color Board::getStoneColorAt (size_t x, size_t y) const
{
    //LOGFUNCTION(cout, "Board::getStoneColorAt");

    return m_points[x][y].getStoneColor();
}

bool Board::isOccupiedPoint (size_t x, size_t y)
{
    LOGFUNCTION(cout, "Board::isOccupiedPoint");

    return !(m_points[x][y].canPlayStone());
}

bool Board::isLibertyPoint (size_t x, size_t y)
{
    LOGFUNCTION(cout, "Board::isLibertyPoint");

    return false;
}

std::vector<Chain> Board::getAllEmptyChains ()
{
    LOGFUNCTION(cout, "Board::getAllEmptyChains");

    std::vector<Chain> emptyChains;
    ConstPointSet alreadyVisited;

    for (size_t row = 0; row < m_points.size(); ++row)
    {
        for (size_t column = 0; column < m_points[row].size(); ++column)
        {
            const Point & point = m_points[row][column];

            if (point.getStoneColor() != Stone::Color::NONE)
                continue;

            try
            {
                //emptyChains.emplace_back(Stone::Color::NONE, point, *this, &alreadyVisited);
                Chain chain(Stone::Color::NONE, point, *this, &alreadyVisited);
                emptyChains.push_back(chain);
//std::cout << "Empty chain starting at [" << row << "," << column << "]" << std::endl;
            }
            catch (int)
            {
            }
        }
    }
    
    return emptyChains;
}

bool Board::placeStoneAt (size_t x, size_t y, std::unique_ptr<Stone> stone)
{
    LOGFUNCTION(cout, "Board::placeStoneAt");

    assert(stone.get() != nullptr);

    m_ko.second = m_points[x][y];

    m_points[x][y].playStone(std::move(stone));

    return true;
}

size_t Board::removeCapturedStones (Stone::Color colorToCapture)
{
    LOGFUNCTION(cout, "Board::removeCapturedStones");

    size_t captureCount = 0;

    ConstPointSet alreadyVisited;

    for (size_t row = 0; row < m_points.size(); ++row)
    {
        for (size_t column = 0; column < m_points[row].size(); ++column)
        {
            try
            {
                Chain currentChain {m_points[row][column], *this, &alreadyVisited};

                if (currentChain.color() == colorToCapture && currentChain.libertyCount() == 0)
                {
                    captureCount += currentChain.size();

                    currentChain.foreach([this](const Point & point)
                    {
                        m_points[point.coordinates.row][point.coordinates.column].removeStone();
                    }); 
                }
            }
            catch (int)
            {
            }
        }
    }

    // Remember this state for the Ko rule
    //
    m_ko.first = (captureCount == 1);

    return captureCount;
}

bool Board::isValidMove (Stone::Color stoneColor, size_t row, size_t column) const
{
    LOGFUNCTION(cout, "Board::isValidMove");

    if (!m_points[row][column].canPlayStone())
    {
        return false;
    }

    Chain potentialChain {stoneColor, m_points[row][column], *this, nullptr};

    ConstPointSet alreadyVisited;

    bool wouldCaptureOpponentChain = false;


    potentialChain.foreach(getOpposingColor(stoneColor),
    [this, &alreadyVisited, &wouldCaptureOpponentChain](const Point & point)
    {
        LOGFUNCTION(cout, "Board::lambda_wouldCapture");

        try
        {
            Chain opponentChain {point, *this, &alreadyVisited};

            if (opponentChain.libertyCount() == 1)
            {
                if (!doesKoRuleApply(opponentChain))
                    wouldCaptureOpponentChain = true;
            }
        }
        catch (int)
        {
        }
    });

    if (potentialChain.libertyCount() == 0)
    {
        return wouldCaptureOpponentChain; 
    }

    return true;
}

bool Board::doesKoRuleApply (const Chain & chain) const
{
    LOGFUNCTION(cout, "Board::doesKoRuleApply");

    if (chain.size() == 1)
    {
        if (m_ko.first && chain.containsPoint(m_ko.second))
            return true;
    }

    return false;
}

} // namespace Go

