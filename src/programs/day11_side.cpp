#include <iostream>

#include "day11_panel.h"
#include "day11_side.h"

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

int Side::getOffset(int pos)
{
    return m_size+pos;
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
            new_side[i+1][j+1].setStatus(m_panels[i][j].getColor(), m_panels[i][j].isPainted());
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
    std::cout << "Printing (" << m_x_position << "," << m_y_position << ") to the color " << color << std::endl;
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
    ShipDirection new_direction = getNextDirection(m_current_direction, direction);
    std::cout << "Turning " << direction << " from " << m_current_direction << " to " << new_direction << std::endl;
    int new_x=m_x_position;
    int new_y=m_y_position;
    int min_val=m_size*-1;
    int max_val=m_size;
    switch (new_direction)
    {
        case north:
            new_y=new_y+1;
            break;
        case south:
            new_y=new_y-1;
            break;
        case east:
            new_x=new_x+1;
            break;
        case west:
            new_x=new_x-1;
            break;
    }
    std::cout << "Moving from (" << m_x_position << "," << m_y_position << ") to (" << new_x << "," << new_y << ")" << std::endl;
    if (new_x<min_val || new_x > max_val || new_y < min_val || new_y > max_val)
    {
        int old_size=m_size;
        expand();
        std::cout << "Grid expanded from " << old_size << " to " << m_size << std::endl;
    }
    m_current_direction=new_direction;
    m_x_position=new_x;
    m_y_position=new_y;
}

void Side::dump(std::ostream & out)
{
    int count=m_size*2+1;
    int shipX=getOffset(m_x_position);
    int shipY=getOffset(m_y_position);
    out << "Grid size is " << m_size << std::endl;
    for (int y=0; y<count; y++) // iterate over rows first
    {
        for (int x=0; x<count; x++) // iterate over columns
        {
            if (x==shipX && y==shipY)
            {
                out << m_current_direction;
            }
            else
            {
                out << m_panels[x][y].getColor();
            }
        }
        out << std::endl;
    }
}

PanelColor Side::getCurrentPanelColor()
{
    int shipX=getOffset(m_x_position);
    int shipY=getOffset(m_y_position);
    return m_panels[shipX][shipY].getColor();
}
