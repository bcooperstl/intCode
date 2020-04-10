#include <iostream>

#include "day15_point.h"

Point::Point(int x, int y, Point * from)
{
    m_x=x;
    m_y=y;
    m_from=from;
    for (int i=0; i<DIRECTION_COUNT; i++)
    {
        m_neighbors[i]=NULL;
    }
}

Point::Point(int x, int y, Point * from, Direction direction_from_from):Point(x,y,from)
{
    std::vector<Direction> fromDirection=from->getPathToHere();
    m_path_to_here.insert(m_path_to_here.end(), fromDirection.begin(), fromDirection.end());
    m_path_to_here.push_back(direction_from_from);
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

int Point::getX()
{
    return m_x;
}

int Point::getY()
{
    return m_y;
}

Point * Point::getNeighbor(Direction direction)
{
    return m_neighbors[direction-1];
}

void Point::setNeighbor(Direction direction, Point * neighbor)
{
    m_neighbors[direction-1]=neighbor;
}

bool Point::isNorthOfOther(Point * other)
{
    if (m_x == other->getX())
    {
        if (m_y == (other->getY() + 1))
        {
            return true;
        }
    }
    return false;
}

bool Point::isEastOfOther(Point * other)
{
    if (m_y == other->getY())
    {
        if (m_x == (other->getX() + 1))
        {
            return true;
        }
    }
    return false;
}

int Point::getOxygenDistance()
{
    return m_oxygen_distance;
}

void Point::setOxygenDistance(int distance)
{
    m_oxygen_distance = distance;
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
