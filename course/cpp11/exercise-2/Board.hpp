#ifndef INCL_BOARD_HPP__
#define INCL_BOARD_HPP__

#include <array>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "Point.hpp"
#include "Chain.hpp"
#include "Stone.hpp"


namespace Go {
	
class Board
{
 public:
    static const int BOARD_SIZE = 9;

 private:

    std::array<std::array<Point, BOARD_SIZE>, BOARD_SIZE> m_points;
    std::pair<bool, std::reference_wrapper<const Point>> m_koState;

 public:
    Board ();

    std::vector<Chain> getAllEmptyChains ();
    StoneColor getStoneColorAt (const PointCoords & coords) const;
    bool isOccupiedPoint (const PointCoords & coords);
    bool isValidMove (StoneColor color, const PointCoords & coords) const;
    void placeStoneAt (const PointCoords & coords, Stone * stone);
    size_t removeCapturedStones (StoneColor colorToCapture);

    const Point & getPointAbove (const Point & point) const;
    const Point & getPointBelow (const Point & point) const;
    const Point & getPointLeft (const Point & point) const;
    const Point & getPointRight (const Point & point) const;

 private:

    Chain calculateChain (const PointCoords & coords);
    bool doesKoRuleApply (const Chain & chain) const;
};

}

#endif /* end of include guard: INCL_BOARD_HPP__ */
