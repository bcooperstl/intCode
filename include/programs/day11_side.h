#ifndef __DAY_11_SIDE_H__
#define __DAY_11_SIDE_H__

#include <iostream>

enum ShipDirection {left='<', up='^', right='>', down='v'};

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
public:
    Side(int size, int startX, int startY, ShipDirection direction);
    ~Side();
    int getPaintedCount();
    void dump(std::ostream & out);
};

#endif
