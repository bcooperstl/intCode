#ifndef __DAY_11_SIDE_H__
#define __DAY_11_SIDE_H__

#include <iostream>

enum ShipDirection {west='<', north='^', east='>', south='v'};
enum TurnDirection {left='L', right='R'};

class Side
{
private:
    Panel ** m_panels;
    int m_size;
    int m_x_position;
    int m_y_position;
    ShipDirection m_current_direction;
    Panel ** allocateSide(int size);
    void deleteSide(int size, Panel ** side);
    int getOffset(int pos);
    void expand();
    ShipDirection getNextDirection(ShipDirection ship, TurnDirection turn);
public:
    Side(int size, int startX, int startY, ShipDirection direction);
    ~Side();
    int getPaintedCount();
    void paint(PanelColor color);
    void turnAndMove(TurnDirection direction);
    void dump(std::ostream & out);
};

#endif
