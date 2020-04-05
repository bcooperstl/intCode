#include <iostream>

#include "day15_point.h"

Point::Point(int x, int y)
{
    m_x=x;
    m_y=y;
    m_explored_neighbors=false;
}

Point::Point(int x, int y, Point * from, Direction direction_from_from):Point(x,y)
{
    m_path_to_here.insert(std::end(m_path_to_here), std::begin(from->getPathToHere()), std::end(from->getPathToHere()));
    m_path_to_here.push_back(direction_from_from);
}

Point::~Point()
{
}

bool Point::isExploredNeighbors()
{
    return m_explored_neighbors;
}

Contents Point::getContents()
{
    return m_contents;
}

void Point::setContents(Contents contents)
{
    m_contents=contents;
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

std::vector<Direction> Point::getPathToHere()
{
    return m_path_to_here;
}

std::vector<Direction> Point::getPathToHome()
{
    std::vector<Direction> ret;
    for (std::vector<Direction>::reverse_iterator rit = m_path_to_here.rbegin(); rit!= m_path_to_here.rend(); ++rit)
    {
        switch (*rit)
        {
            case North:
                ret.push_back(South);
                break;
            case South:
                ret.push_back(North);
                break;
            case East:
                ret.push_back(West);
                break;
            case West:
                ret.push_back(East);
                break;
        }
    }
    return ret;
}
