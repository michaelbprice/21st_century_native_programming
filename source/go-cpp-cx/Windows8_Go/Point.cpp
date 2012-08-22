#include "pch.h"
#include "Point.hpp"
#include "Stone.hpp"
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

namespace Go {

StoneColor Point::getStoneColor () const
{
    if (m_stone.get() == nullptr)
        return StoneColor::NONE;

    return m_stone->getColor();
}

void Point::playStone (std::unique_ptr<Stone> stone)
{
    swap(m_stone, stone);
}

bool Point::canPlayStone () const
{
    return m_stone.get() == nullptr;
}

void Point::removeStone ()
{ 
    m_stone.reset();
}

} // namespace Go

wostream & operator<< (wostream & out, const Go::PointCoords & coords)
{
	out << L"[" << coords.row << L"," << coords.column << L"]";
	return out;
}

wostream & operator<< (wostream & out, const Go::Point & point)
{
	out << L"Point: {" << point.coordinates << L", ";

	if (point.m_stone.get())
		out << *point.m_stone;
	else
		out << L"{null}";

    out << L"}";
	return out;
}