#include <iostream>
#include <algorithm>

#include "day15_area.h"
#include "day15_point.h"

Area::Area()
{
    m_min_x=0;
    m_max_x=0;
    m_min_y=0;
    m_max_y=0;
    m_oxygen_location=NULL;
    m_start_location=NULL;
}

Area::~Area()
{
    for (int i=0; i<m_points.size(); i++)
    {
        delete m_points[i];
    }
}

Point * Area::getPoint(int x, int y)
{
    for (int i=0; i<m_points.size(); i++)
    {
        if (m_points[i]->getX()==x && m_points[i]->getY()==y)
            return m_points[i];
    }
    return NULL;
}

void Area::addPoint(Point * point)
{
    if (m_points.size() == 0)
        m_start_location=point;
    if (point->getContents()==OxygenSensor)
        m_oxygen_location=point;
    
    m_points.push_back(point);
    if (point->getContents()!=Wall)
        m_points_to_explore.push_back(point);
    
    if (point->getX() < m_min_x)
        m_min_x=point->getX();
    if (point->getX() > m_max_x)
        m_max_x=point->getX();
    if (point->getY() < m_min_y)
        m_min_y=point->getY();
    if (point->getY() > m_max_y)
        m_max_y=point->getY();
}

Point * Area::getNextPointToExplore()
{
    if (m_points_to_explore.size() > 0)
        return m_points_to_explore[0];
    return NULL;
}

void Area::removeExploredPoint(Point * point)
{
    std::vector<Point *>::iterator it = m_points_to_explore.begin();
    while (it != m_points_to_explore.end())
    {
        if (*it==point)
            it=m_points_to_explore.erase(it);
        else
            ++it;
    }
}

void Area::setNorthSouthPair(Point * north, Point * south)
{
    north->setNeighbor(South, south);
    south->setNeighbor(North, north);
}

void Area::setEastWestPair(Point * east, Point * west)
{
    east->setNeighbor(West, west);
    west->setNeighbor(East, east);
}

void Area::pairPoints()
{
    for (int i=0; i<m_points.size(); i++)
    {
        for (int j=0; j<m_points.size(); j++)
        {
            if (i==j)
                continue; // a point will never be north or east of itself
            Point * iPoint=m_points[i];
            Point * jPoint=m_points[j];
            if (iPoint->isNorthOfOther(jPoint))
            {
#ifdef DEBUG_PROGRAMS
                std::cerr << "Point (" << iPoint->getX() << "," << iPoint->getY() << ") is North of point (" << jPoint->getX() << "," << jPoint->getY() << ")" << std::endl;
#endif
                setNorthSouthPair(iPoint,jPoint);
            }
            if (iPoint->isEastOfOther(jPoint))
            {
#ifdef DEBUG_PROGRAMS
                std::cerr << "Point (" << iPoint->getX() << "," << iPoint->getY() << ") is East of point (" << jPoint->getX() << "," << jPoint->getY() << ")" << std::endl;
#endif
                setEastWestPair(iPoint,jPoint);
            }
        }
    }
}

void Area::setDistanceToOxygenSensor()
{
    int level=0;
    std::vector<Point *> currLevel;
    std::vector<Point *> nextLevel;
    std::vector<Point *> allNonWallPoints;
    
    for (int i=0; i<m_points.size(); i++)
    {
        if (m_points[i]->getContents()!=Wall)
        {
            allNonWallPoints.push_back(m_points[i]);
            m_points[i]->setOxygenDistance(-1);
        }
    }

    currLevel.push_back(m_oxygen_location);
    
    while (!allNonWallPoints.empty())
    {
#ifdef DEBUG_PROGRAMS
        std::cerr << "Level " << level << ": There are " << allNonWallPoints.size() << " unworked points to work and " << currLevel.size() << " points in the current level" << std::endl;
#endif
        
        for (int i=0; i<currLevel.size(); i++)
        {
            Point * current=currLevel[i];
            current->setOxygenDistance(level);

#ifdef DEBUG_PROGRAMS
            std::cerr << "  Setting distance to " << level << " on (" << current->getX() << "," << current->getY() << ")" << std::endl;
#endif
            
            allNonWallPoints.erase(std::remove(allNonWallPoints.begin(), allNonWallPoints.end(), current), allNonWallPoints.end());
            
            Point * north=current->getNeighbor(North);
            Point * south=current->getNeighbor(South);
            Point * east=current->getNeighbor(East);
            Point * west=current->getNeighbor(West);
            if (north->getContents()!=Wall && north->getOxygenDistance()==-1)
            {
#ifdef DEBUG_PROGRAMS
                std::cerr << "    Adding north point of (" << north->getX() << "," << north->getY() << ") to nextLevel" << std::endl;
#endif
                nextLevel.push_back(north);
            }
            if (south->getContents()!=Wall && south->getOxygenDistance()==-1)
            {
#ifdef DEBUG_PROGRAMS
                std::cerr << "    Adding south point of (" << south->getX() << "," << south->getY() << ") to nextLevel" << std::endl;
#endif
                nextLevel.push_back(south);
            }
            if (east->getContents()!=Wall && east->getOxygenDistance()==-1)
            {
#ifdef DEBUG_PROGRAMS
                std::cerr << "    Adding east point of (" << east->getX() << "," << east->getY() << ") to nextLevel" << std::endl;
#endif
                nextLevel.push_back(east);
            }
            if (west->getContents()!=Wall && west->getOxygenDistance()==-1)
            {
#ifdef DEBUG_PROGRAMS
                std::cerr << "    Adding west point of (" << west->getX() << "," << west->getY() << ") to nextLevel" << std::endl;
#endif
                nextLevel.push_back(west);
            }
        }
        
        level++;
        currLevel.clear();
        currLevel=nextLevel;
        nextLevel.clear();
    }
}

int Area::getMaximumDistanceToOxygen()
{
    int max=-1;
    for (int i=0; i<m_points.size(); i++)
    {
        if (m_points[i]->getOxygenDistance()>max)
            max=m_points[i]->getOxygenDistance();
    }
    return max;
}

void Area::display(std::ostream & out, int droidX, int droidY)
{
    out << "  ";
    for (int x=m_min_x; x<=m_max_x; x++)
    {
        if (x==0)
        {
            out << "0";
        }
        else if (x%10==0)
        {
            out << "|";
        }
        else
        {
            out << " ";
        }
    }
    out << std::endl;
    for (int y=m_max_y; y>=m_min_y; y--)
    {
        if (y==0)
        {
            out << "0 ";
        }
        else if (y%10==0)
        {
            out << "- ";
        }
        else
        {
            out << "  ";
        }
        for (int x=m_min_x; x<=m_max_x; x++)
        {
            Point * pt = getPoint(x, y);
            if (x==droidX && y==droidY)
            {
                out << 'D';
            }
            else if (pt!=NULL)
            {
                pt->display(out);
            }
            else
            {
                out << ' ';
            }
        }
        out << std::endl;
    }
}
