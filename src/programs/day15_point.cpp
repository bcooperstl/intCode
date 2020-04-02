#include <iostream>

#include "day15_point.h"

Point::Point(int x, int y, Point * from)
{
    m_x=x;
    m_y=y;
    m_from=from;
}

Point::~Point()
{
}

Contents Point::getContents()
{
    return m_contents;
}

void Point::setContents(Contents contents)
{
    m_contents=contents;
}

Point * Point::getFrom()
{
    return m_from;
}

int Point::getX()
{
    return m_x;
}

int Point::getY()
{
    return m_y;
}

void Point::display(std::ostream & out)
{
    if (m_contents==Wall)
        out << '#';
    else if (m_contents==WalkingArea)
        out << '.';
    else if (m_contents==OxygenSensor)
        out << 'o';
}
