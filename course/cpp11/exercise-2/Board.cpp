#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

#include "Board.hpp"
#include "Chain.hpp"
#include "Logger.hpp"
#include "Stone.hpp"

using namespace std;

namespace Go {

Board::Board ()
  : m_koState(false, m_points[0][0])
{
    for (size_t row = 0; row < BOARD_SIZE; ++row)
    {
        for (size_t column =0; column < BOARD_SIZE; ++column)
        {
            m_points[row][column].coordinates.row = row; 
            m_points[row][column].coordinates.column = column; 
        }
    }
}

bool Board::doesKoRuleApply (const Chain & potentiallyCapturedChain) const
{
    // IF the potentially captured chain has only one stone AND
    // the potentially captured stone was the stone the opposing player just played (m_koState.second) AND
    // the previously played stone had captured a single stone (m_koState.first)
    // THEN the Ko rule applies and the move is invalid.
    //
    if (potentiallyCapturedChain.size() == 1)
    {
        if (m_koState.first && potentiallyCapturedChain.containsPoint(m_koState.second))
        {
            gLogger.log(LogLevel::kMedium, "The Ko rule was enforced");
            return true;
        }
    }

    return false;
}

std::vector<Chain> Board::getAllEmptyChains ()
{
    std::vector<Chain> emptyChains;

    // A set of points that we've already examined. This helps prevents some
    // bad recursion and keeps a chain from being "found" once for each stone
    // in the chain.
    //
    ConstPointSet alreadyVisited;

    for (size_t row = 0; row < m_points.size(); ++row)
    {
        for (size_t column = 0; column < m_points[row].size(); ++column)
        {
            const Point & point = m_points[row][column];

            // We are only looking for points without a stone, so get out
            // of here if there is a stone on this point
            //
            if (point.getStoneColor() != StoneColor::NONE)
                continue;

            // If the point we are considering has already been visited,
            // then Chain's ctor will throw a PointVisitedAlreadyException
            // object. We can safely swallow that exception and move on
            // to the next point.
            //
            try
            {
                // TODO: figure out why this didn't work... emptyChains.emplace_back(StoneColor::NONE, point, *this, &alreadyVisited);
                Chain chain(StoneColor::NONE, point, *this, &alreadyVisited);
                emptyChains.push_back(chain);
                gLogger.log(LogLevel::kMedium, "Discovered empty chain");
            }
            catch (const Chain::PointVisitedAlreadyException & ex)
            {
                gLogger.log(LogLevel::kFirehose, "Skipping point");
            }
        }
    }
    
    return emptyChains;
}

const Point & Board::getPointAbove (const Point & point) const
{
    try
    {
        return m_points.at(point.coordinates.row - 1).at(point.coordinates.column);
    }
    catch (const out_of_range & ex)
    {
        return point;
    }
}

const Point & Board::getPointBelow (const Point & point) const
{
    try
    {
        return m_points.at(point.coordinates.row + 1).at(point.coordinates.column);
    }
    catch (const out_of_range & ex)
    {
        return point;
    }
}

const Point & Board::getPointLeft (const Point & point) const
{
    try
    {
        return m_points.at(point.coordinates.row).at(point.coordinates.column - 1);
    }
    catch (const out_of_range & ex)
    {
        return point;
    }
}

const Point & Board::getPointRight (const Point & point) const
{
    try
    {
        return m_points.at(point.coordinates.row).at(point.coordinates.column + 1);
    }
    catch (const out_of_range & ex)
    {
        return point;
    }
}

StoneColor Board::getStoneColorAt (const PointCoords & coords) const
{
    return m_points.at(coords.row).at(coords.column).getStoneColor();
}

bool Board::isOccupiedPoint (const PointCoords & coords)
{
    return !(m_points.at(coords.row).at(coords.column).canPlayStone());
}

bool Board::isValidMove (StoneColor stoneColor, const PointCoords & coords) const
{
    if (isPassingCoordinates(coords))
    {
        return true;
    }

    const Point & thePoint = m_points.at(coords.row).at(coords.column);

    // Easy Case: If there is already a stone there, then this cannot be a
    // valid move.
    //
    if (!thePoint.canPlayStone())
    {
        return false;
    }


    // Hard Case: If the spot we intend to play at would result in an
    // immediate capture of our stones, then the move is disallowed.
    // This is called the suicide rule. The one exception is in the case
    // where we would also capture one or more stones from the opponent.
    // Of course, that exception is also governed by the 'Ko' rule
    //

    // Caclulate what the chain would look like if the stone were placed
    // at the desired location
    //
    Chain potentialChain (stoneColor, thePoint, *this, nullptr);

    // A set of points that we've already examined. This helps prevents some
    // bad recursion and keeps a chain from being "found" once for each stone
    // in the chain.
    //
    ConstPointSet alreadyVisited;

    bool wouldCaptureOpponentChain = false;

    // For each point on the border of the potential chain that is occupied
    // by an opponent's stone, calculate it's chain.
    //
    // If the chain only has a single liberty (which would promptly be
    // taken by this move) and the 'Ko' rule does not apply, then we would
    // in fact capture at least one opponent stone.
    // 
    for (const Point * ptrPoint : potentialChain.getSurroundingPoints(getOpposingColor(stoneColor)))
    {
        const Point & point = *ptrPoint;

        bool opponentThreatened = false;

        // If the point we are considering has already been visited,
        // then Chain's ctor will throw a PointVisitedAlreadyException
        // object. We can safely swallow that exception and move on
        // to the next point.
        //
        try
        {
            Chain opponentChain (point, *this, &alreadyVisited);

            gLogger.log(LogLevel::kMedium, "Discovered chain");

            // If this move would take the last liberty from a chain of the opponent and
            // if the 'Ko' rule doesn't apply, then we would indeed capture
            // their stones
            //
            if (opponentChain.libertyCount() == 1)
            {
                if (!doesKoRuleApply(opponentChain))
                    wouldCaptureOpponentChain = true;
            }
        }
        catch (const Chain::PointVisitedAlreadyException & ex)
        {
            gLogger.log(LogLevel::kFirehose, "Skipping point");
        }
    }

    // If making this move would result in our chain not having any liberties,
    // it is only valid if we end up capturing an opposing chain (per the
    // restrictions from above); otherwise, it is a valid move.
    //
    if (potentialChain.libertyCount() == 0)
    {
        return wouldCaptureOpponentChain; 
    }

    return true;
}

void Board::placeStoneAt (const PointCoords & coords, Stone * stone)
{
    assert(stone != nullptr);

    Point & thePoint = m_points.at(coords.row).at(coords.column);

    // Remember this point for implementing the 'Ko' rule
    //
    m_koState.second = thePoint;

    // Actually play the stone
    //
    thePoint.playStone(stone);
}

size_t Board::removeCapturedStones (StoneColor colorToCapture)
{
    size_t captureCount = 0;

    // A set of points that we've already examined. This helps prevents some
    // bad recursion and keeps a chain from being "found" once for each stone
    // in the chain.
    //
    ConstPointSet alreadyVisited;

    for (size_t row = 0; row < m_points.size(); ++row)
    {
        for (size_t column = 0; column < m_points[row].size(); ++column)
        {
            const Point & thePoint = m_points.at(row).at(column);

            // If the point we are considering has already been visited,
            // then Chain's ctor will throw a PointVisitedAlreadyException
            // object. We can safely swallow that exception and move on
            // to the next point.
            //
            try
            {                
                Chain currentChain (thePoint, *this, &alreadyVisited);

                gLogger.log(LogLevel::kMedium, "Discovered chain");

                // If the chain we are looking at is the color we should consider capturing and
                // the chain has no liberties, then capture it
                // 
                if (currentChain.color() == colorToCapture && currentChain.libertyCount() == 0)
                {
                    captureCount += currentChain.size();

                    // For each point in the chain, remove the stone from the board
                    // at those coordniates
                    //
                    for (const Point * point : currentChain.getPointsInChain())
                    {
                        m_points[point->coordinates.row][point->coordinates.column].removeStone();
                    }; 
                }
            }
            catch (const Chain::PointVisitedAlreadyException & ex)
            {
                gLogger.log(LogLevel::kFirehose, "Skipping point");
            }
        }
    }

    // If we ended up only capturing one stone, the 'Ko' rule might affect
    // the next move, so remember that fact!
    //
    m_koState.first = (captureCount == 1);

    return captureCount;
}

} // namespace Go

