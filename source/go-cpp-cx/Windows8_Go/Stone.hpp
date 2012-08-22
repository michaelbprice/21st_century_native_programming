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
	
class Stone final
{
 public:
    static const size_t kDefaultBlackCount = 21;
    static const size_t kDefaultWhiteCount = 20;

 private:
    StoneColor m_color;

 public:
    Stone (StoneColor color) : m_color(color) { }
    ~Stone () { }

    //Stone(const Stone&) = delete;
    //Stone & operator= (const Stone&) = delete;

    Stone(Stone && other) : m_color(other.m_color) { }
    Stone & operator= (Stone && other)
    {
        if (this != &other)
        {
            this->m_color = other.m_color;
        }
        return *this;
    }

    StoneColor getColor () const;
};

typedef std::vector<std::unique_ptr<Stone>> Stones;

}

std::wostream & operator<< (std::wostream & out, const Go::Stone & stone);


#endif /* end of include guard: INCL_STONE_HPP__ */
