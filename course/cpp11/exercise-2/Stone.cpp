#include "Stone.hpp"

#include <ostream>

using namespace std;

namespace Go {

StoneColor Stone::getColor () const
{
    return m_color;
}

StoneColor getOpposingColor (StoneColor color)
{
    if (color == StoneColor::NONE)
        return color;

    return (color == StoneColor::BLACK) ? StoneColor::WHITE : StoneColor::BLACK;
}

}

