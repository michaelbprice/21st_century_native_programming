#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include "Board.hpp"
#include "Chain.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "Stone.hpp"
#include "Point.hpp"

using namespace std;


namespace Go
{

template <typename TyPlayerUI>
Player<TyPlayerUI>::Player (const string & name)
  : m_ui(*this)
  , m_name(name)
  , m_capturedCount(0)
  , m_nextStone(0)
  , m_pBoard(nullptr)
{
}

template <typename TyPlayerUI>
Player<TyPlayerUI>::~Player ()
{
    for (Stone * stone : m_stones)
        delete stone;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::addToCaptured (size_t numCaptured)
{
    m_capturedCount += numCaptured;
}

template <typename TyPlayerUI>
size_t Player<TyPlayerUI>::calculateScore () const
{
    size_t territoryCount = 0;

    for (Chain & chain : m_pBoard->getAllEmptyChains())
    {
        assert(chain.color() == StoneColor::NONE);

        StoneColor opponentColor = getOpposingColor(m_stoneColor);

        if (chain.borderCountOf(opponentColor) > 0)
            continue;

        if (chain.borderCountOf(m_stoneColor) > 0)
            territoryCount += chain.size();
    }

    return territoryCount + m_capturedCount;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::chooseName ()
{
    m_name =  m_ui.promptForName();
}

template <typename TyPlayerUI>
StoneColor Player<TyPlayerUI>::chooseStoneColor ()
{
    setStoneColor(m_ui.promptForStoneColor());

    return m_stoneColor;
}

template <typename TyPlayerUI>
const Board & Player<TyPlayerUI>::getGameBoard () const
{
    assert (m_pBoard != nullptr);

    return *m_pBoard;
}

template <typename TyPlayerUI>
const string & Player<TyPlayerUI>::getName () const
{
    return m_name;
}

template <typename TyPlayerUI>
StoneColor Player<TyPlayerUI>::getStoneColor ()
{
    return m_stoneColor;
}

template <typename TyPlayerUI>
bool Player<TyPlayerUI>::hasStones () const
{
    return m_stones.size() > m_nextStone;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyGameReady ()
{
    m_ui.updateGameState();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyLost ()
{
    m_ui.onLoss();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyTied ()
{
    m_ui.onTie();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyTurn ()
{
    m_ui.updateGameState();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::notifyWon ()
{
    m_ui.onWin();
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setGameBoard (Board & board)
{
    assert(m_pBoard == nullptr);

    m_pBoard = &board;;
}

template <typename TyPlayerUI>
void Player<TyPlayerUI>::setStoneColor (StoneColor color)
{
    m_stoneColor = color;

    size_t numberOfStones = 0;

    if (m_stoneColor == StoneColor::BLACK)
    {
        numberOfStones = Stone::kDefaultBlackCount;
    }
    else
    {
        numberOfStones = Stone::kDefaultWhiteCount;
    }

    m_stones.reserve(numberOfStones);

    for (size_t i = 0; i < numberOfStones; ++i)
    {
        m_stones.emplace_back(new Stone(m_stoneColor));
    }
}

template <typename TyPlayerUI>
PointCoords Player<TyPlayerUI>::playStone ()
{
    assert(m_pBoard != nullptr);

    gLogger.log(LogLevel::kMedium, "About to prompt for move input");
    PointCoords theMove = m_ui.promptForMove();

    while (!m_pBoard->isValidMove(m_stones.back()->getColor(), theMove))
    {
        gLogger.log(LogLevel::kMedium, "Invalid move");
        m_ui.onInvalidMove(theMove);
        theMove = m_ui.promptForMove();
    }

    if (!isPassingCoordinates(theMove))
    {
        m_pBoard->placeStoneAt(theMove, m_stones[m_nextStone]);
        m_nextStone++;
    }

    return theMove;
}

}
