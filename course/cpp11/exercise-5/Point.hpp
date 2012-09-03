#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

#include <functional>
#include <iosfwd>
#include <memory>
#include <unordered_set>

#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"

std::ostream & operator<< (std::ostream & out, const Go::PointCoords & coords);
std::ostream & operator<< (std::ostream & out, const Go::Point & point);

namespace Go {

struct PointCoords
{
    PointCoords () : row(0), column(0) { }
    PointCoords (size_t r, size_t c) : row(r), column(c) { }

    size_t row;
    size_t column;
};

bool isPassingCoordinates (const PointCoords & move);

class Point final
{
 friend std::ostream & ::operator<< (std::ostream & out, const Go::Point & point);

 private:
    Stone * m_stone;

 public:
    Point () : m_stone(nullptr) { }

    PointCoords coordinates;

    StoneColor getStoneColor () const;

    void playStone (Stone * stone);

    bool canPlayStone () const;

    void removeStone ();
};

} // namespace Go



#endif /* end of include guard: INCL_POINT_HPP__ */
