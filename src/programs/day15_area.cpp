#include <iostream>

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

void Area::display(std::ostream & out, int droidX, int droidY)
{
    for (int y=m_min_y; y<=m_max_y; y++)
    {
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
