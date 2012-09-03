#include "Board.hpp"
#include "Point.hpp"
#include "Stone.hpp"
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Go {

bool isPassingCoordinates (const PointCoords & move)
{
  return move.row >= Board::BOARD_SIZE || move.column >= Board::BOARD_SIZE;
}

StoneColor Point::getStoneColor () const
{
    if (m_stone == nullptr)
        return StoneColor::NONE;

    return m_stone->getColor();
}

void Point::playStone (Stone * stone)
{
    m_stone = stone;
}

bool Point::canPlayStone () const
{
    return m_stone == nullptr;
}

void Point::removeStone ()
{ 
    m_stone = nullptr;
}


} // namespace Go

