#ifndef __DAY_15_POINT_H__
#define __DAY_15_POINT_H__

#define DIRECTION_COUNT 4

enum Contents {Wall=0, WalkingArea=1, OxygenSensor=2};
enum Direction {North=1, South=2, West=3, East=4};

class Point
{
private:
    int m_x;
    int m_y;
    Point * m_from;
    Contents m_contents;
    bool m_explored_directions[DIRECTION_COUNT];
public:
    Point(int x, int y, Point * from);
    ~Point();
    int getX();
    int getY();
    Contents getContents();
    void setContents(Contents contents);
    Point * getFrom();
    void display(std::ostream & out);
};

#endif
