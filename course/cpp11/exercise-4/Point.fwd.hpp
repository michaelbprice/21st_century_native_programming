#ifndef INCL_POINT_FWD_HPP__
#define INCL_POINT_FWD_HPP__

#include <functional>
#include <unordered_set>

namespace Go {

class Point;
class PointCoords;

typedef std::unordered_set<Point*> PointSet;
typedef std::unordered_set<const Point*> ConstPointSet ;

} // namespace Go

#endif /* end of include guard: INCL_POINT_FWD_HPP__ */
