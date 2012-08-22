#include "pch.h"
#include "Stone.hpp"

#include <ostream>

using namespace std;

namespace Go
{

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

wostream & operator<< (wostream & out, const Go::Stone & stone)
{
	using namespace Go;
	out << L"Stone: {";

	switch (stone.getColor())
	{
     case StoneColor::NONE: out << L"Empty"; break;
     case StoneColor::BLACK: out << L"Black"; break;
     case StoneColor::WHITE: out << L"White"; break;
	}

    out << L"}";
    return out;
}
