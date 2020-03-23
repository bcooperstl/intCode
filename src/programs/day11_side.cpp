#include "day11_panel.h"
#include "day11_side.h"

int Side::getOffset(int pos)
{
    return m_size+pos;
}

Side::Side(int size, int startX, int startY, ShipDirection direction)
{
    m_size=size;
    m_x_position=startX;
    m_y_position=startY;
    m_current_direction=direction;
    m_panels=allocateSide(m_size);
}

Side::~Side()
{
    deleteSide(m_size, m_panels);
}

void Side::expand()
{
    int new_size = m_size+1;
    int old_alloc_size = 2*m_size+1;
    Panel ** new_side=allocateSide(new_size);
    for (int i=0; i<old_alloc_size; i++)
    {
        for (int j=0; j<old_alloc_size; j++)
        {
            new_side[i+1][j+1]=m_panels[i][j];
        }
    }
    deleteSide(m_size, m_panels);
    m_panels = new_side;
    m_size = new_size;
}

Panel ** Side::allocateSide(int size)
{
    int alloc_size = size*2+1;
    Panel ** ret = new Panel * [alloc_size];
    for (int i=0; i<alloc_size; i++)
    {
        ret[i] = new Panel [alloc_size];
    }
    return ret;
}

void Side::deleteSide(int size, Panel ** side)
{
    int alloc_size = size*2+1;
    for (int i=0; i<alloc_size; i++)
    {
        delete side[i];
    }
    delete side;
}

int Side::getPaintedCount()
{
    int count=0;
    int alloc_size = m_size*2+1;
    for (int i=0; i<alloc_size; i++)
    {
        for (int j=0; j<alloc_size; j++)
        {
            if (m_panels[i][j].isPainted())
                count++;
        }
    }
    return count;
}

void Side::paint(PanelColor color)
{
    m_panels[m_x_position][m_y_position].paint(color);
}

ShipDirection Side::getNextDirection(ShipDirection ship, TurnDirection turn)
{
    switch (turn)
    {
        case left:
        switch (ship)
        {
            case north:
                return west;
            case west:
                return south;
            case south:
                return east;
            case east:
                return north;
        }
        case right:
        {
            case north:
                return east;
            case west:
                return north;
            case south:
                return west;
            case east:
                return south;
        }
    }
    return north; // should never get here
}

void Side::turnAndMove(TurnDirection direction)
{
    
}
