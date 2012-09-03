#ifndef INCL_CHAIN_HPP__
#define INCL_CHAIN_HPP__

#include <functional>
#include <unordered_map>
#include "std.fwd.hpp"
#include "Board.fwd.hpp"
#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"


namespace Go {

class Chain final
{
 private:
    std::unordered_map<StoneColor, ConstPointSet> m_chainAndNeighbors;
    const Point & m_startPoint;
    StoneColor m_color; // Inline assignment would need full definition!!!

 public:
    struct PointVisitedAlreadyException { };

    // Construct a chain from the actual state of a point
    Chain (const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

    // Construct a chain from the potential state of a point
    Chain (StoneColor stoneColor, const Point & startPoint, const Board & board, ConstPointSet * pointsToIgnore);

    size_t borderCountOf (StoneColor color);
    StoneColor color () const;
    bool containsPoint (const Point & point) const;
    ConstPointSet & getPointsInChain ();
    ConstPointSet & getSurroundingPoints (StoneColor color);
    size_t libertyCount () const;
    size_t size () const;

 private:
    void doChainCalculation (const Point & point, const Board & board, ConstPointSet & pointsToIgnore);
    void doTest (const Point & testPoint, const Board & board, const Point & point, ConstPointSet & pointsToIgnore);
};

} // namespace Go

#endif /* end of include guard: INCL_CHAIN_HPP__ */
