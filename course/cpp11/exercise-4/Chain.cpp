#include "Chain.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include "Board.hpp"
#include "Logger.hpp"
#include "Point.hpp"
#include "Stone.hpp"

namespace Go {

using namespace std;

Chain::Chain (StoneColor stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore)
  : m_color(stoneColor)
  , m_startPoint(startPoint)
{
    m_chainAndNeighbors[StoneColor::NONE] = ConstPointSet();
    m_chainAndNeighbors[StoneColor::BLACK] = ConstPointSet();
    m_chainAndNeighbors[StoneColor::WHITE] = ConstPointSet();

    // If we were given a set of points to ignore, then we must determine if we've
    // seen the given point before.  If we have, then we should stop constructing
    // this chain and throw the appropriate exception.
    //
    if (pointsToIgnore != nullptr)
    {
        if (pointsToIgnore->find(&startPoint) != pointsToIgnore->end())
            throw PointVisitedAlreadyException();
    }

    // While we are calculating the chain and its neighbors, we would like to
    // track points we've seen seperately since many neighbors could have also
    // been identified as a part of a previous chain in another step.
    //
    ConstPointSet myPointsToIgnore;

    doChainCalculation(startPoint, board, myPointsToIgnore); 

    // If we were given a set of points to ignore, then merge the two
    // ignore sets
    //
    if (pointsToIgnore != nullptr)
    {
        pointsToIgnore->insert(begin(myPointsToIgnore), end(myPointsToIgnore));
    }
}

Chain::Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore)
  : Chain(startPoint.getStoneColor(), startPoint, board, pointsToIgnore)
{
}

void Chain::doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore)
{
    // If we've seen this point before then we don't have to do anything.
    //
    if (pointsToIgnore.find(&point) != pointsToIgnore.end())
        return;

    // Add the point to the list of Points that we've processed already.
    //
    pointsToIgnore.insert(&point);

    // Insert the current Point into the current chain
    //
    m_chainAndNeighbors[m_color].insert(&point);

    // Visit each point that neighbors this one, and test that point to see
    // if it a)belongs to the current chain, b)belongs to an opponent's
    // chain, or c)belongs to an "empty" chain
    //
    doTest(board.getPointAbove(point), board, point, pointsToIgnore);
    doTest(board.getPointBelow(point), board, point, pointsToIgnore);
    doTest(board.getPointLeft(point), board, point, pointsToIgnore);
    doTest(board.getPointRight(point), board, point, pointsToIgnore);
}

void Chain::doTest (const Point & testPoint, const Board & board, const Point & point, ConstPointSet & pointsToIgnore)
{
    if ((&testPoint != &m_startPoint) && (&testPoint != &point))
    {
        // If the point we're testing has a stone whose color matchers
        // our own, then recurse on that point; otherwise insert the
        // point into the appropriate map
        //
        if (testPoint.getStoneColor() == m_color)
        {
            doChainCalculation(testPoint, board, pointsToIgnore);
        }
        else
        {
            ConstPointSet & set = m_chainAndNeighbors.at(testPoint.getStoneColor());

            if (set.find(&testPoint) == set.end())
            {
                set.insert(&testPoint);
            }
        }
    }    
}

size_t Chain::borderCountOf (StoneColor color)
{
    assert(color != m_color);

    return m_chainAndNeighbors.at(color).size();
}

StoneColor Chain::color () const
{
    return m_color;
}

ConstPointSet & Chain::getPointsInChain ()
{
    return getSurroundingPoints(m_color);
}

ConstPointSet & Chain::getSurroundingPoints (StoneColor color)
{
    return m_chainAndNeighbors[color];
}

size_t Chain::libertyCount () const
{
    return m_chainAndNeighbors.at(StoneColor::NONE).size();
}

size_t Chain::size () const
{
    return m_chainAndNeighbors.at(m_color).size();
}

bool Chain::containsPoint (const Point & point) const
{
    const ConstPointSet & theChain = m_chainAndNeighbors.at(m_color);
    return (theChain.find(&point) != theChain.end());
}

} // namespace Go

