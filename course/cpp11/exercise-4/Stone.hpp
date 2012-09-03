#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <iosfwd>
#include <memory>
#include <vector>

#include "Stone.fwd.hpp"

namespace Go
{

enum class StoneColor : unsigned char
{
    NONE,
    BLACK,
    WHITE
};

StoneColor getOpposingColor (StoneColor color);
	
class Stone
{
 public:
    static const size_t kDefaultBlackCount = 3;
    static const size_t kDefaultWhiteCount = 2;

 private:
    const StoneColor m_color;

 public:
    Stone (StoneColor color) : m_color(color) { }

    StoneColor getColor () const;
};

}

#endif /* end of include guard: INCL_STONE_HPP__ */
