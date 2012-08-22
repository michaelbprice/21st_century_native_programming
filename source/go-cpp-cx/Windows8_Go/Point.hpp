#ifndef INCL_POINT_HPP__
#define INCL_POINT_HPP__

#include <functional>
#include <iosfwd>
#include <memory>
#include <unordered_set>
#include "Stone.hpp"

#include "Point.fwd.hpp"

std::wostream & operator<< (std::wostream & out, const Go::PointCoords & coords);
std::wostream & operator<< (std::wostream & out, const Go::Point & point);


namespace Go {

struct PointCoords final
{
    PointCoords () : row(0), column(0) { }
    PointCoords (size_t r, size_t c) : row(c), column(c) { }

    size_t row;
    size_t column;
};

class Point final
{
 friend std::wostream & ::operator<< (std::wostream & out, const Point & point);

 private:
    std::unique_ptr<Stone> m_stone;

    Point (const Point &);

 public:
    Point () : m_stone(nullptr) { }

    PointCoords coordinates;

    StoneColor getStoneColor () const;

    void playStone (std::unique_ptr<Stone> stone);

    bool canPlayStone () const;

    void removeStone ();
};

typedef std::unordered_set<Point*> PointSet;
typedef std::unordered_set<const Point*> ConstPointSet;

typedef std::function<void(const Point &)> PointVisitorFn;

} // namespace Go


#endif /* end of include guard: INCL_POINT_HPP__ */
