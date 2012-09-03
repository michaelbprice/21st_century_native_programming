#ifndef INCL_STONE_HPP__
#define INCL_STONE_HPP__

#include <iosfwd>
#include <memory>
#include <vector>

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
    StoneColor m_color;

 public:
    Stone (StoneColor color) : m_color(color) { }

    StoneColor getColor () const;
};

using Stones = std::vector<Stone*>;

}

std::ostream & operator<< (std::ostream & out, const Go::Stone & stone);


#endif /* end of include guard: INCL_STONE_HPP__ */
