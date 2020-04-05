#ifndef __DAY_15_AREA_H__
#define __DAY_15_AREA_H__

#include <vector>

#include "day15_point.h"

class Area
{
private:
    int m_min_x;
    int m_max_x;
    int m_min_y;
    int m_max_y;
    Point * m_oxygen_location;
    Point * m_start_location;
    std::vector<Point *> m_points;
    std::vector<Point *> m_points_to_explore;
public:
    Area();
    ~Area();
    Point * getPoint(int x, int y);
    void addPoint(Point * point);
    void display(std::ostream & out, int droidX, int droidY);
    Point * getNextPointToExplore();
    void removeExploredPoint(Point * point);
};

#endif
