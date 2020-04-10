#ifndef __DAY_15_POINT_H__
#define __DAY_15_POINT_H__

#define DIRECTION_COUNT 4

#include <vector>

enum Contents {Wall=0, WalkingArea=1, OxygenSensor=2};
enum Direction {North=1, South=2, West=3, East=4};

class Point
{
private:
    int m_x;
    int m_y;
    Point * m_from;
    Contents m_contents;
    std::vector<Direction> m_path_to_here;
    int m_oxygen_distance;
    Point * m_neighbors[DIRECTION_COUNT];
public:
    Point(int x, int y, Point * from);
    Point(int x, int y, Point * from, Direction direction_from_from);
    ~Point();
    int getX();
    int getY();
    Contents getContents();
    void setContents(Contents contents);
    Point * getFrom();
    void display(std::ostream & out);
    std::vector<Direction> getPathToHere();
    std::vector<Direction> getPathToHome();
    int getOxygenDistance();
    void setOxygenDistance(int distance);
    Point * getNeighbor(Direction direction);
    void setNeighbor(Direction direction, Point * neighbor);
    bool isNorthOfOther(Point * other);
    bool isEastOfOther(Point * other);
};

#endif
