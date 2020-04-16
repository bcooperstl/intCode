#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day17_runner.h"
#include "runner.h"

Day17Runner::Day17Runner(std::string name, InputterOutputter * inputs, Screen * screen):Runner(name)
{
    m_inputs = inputs;
    m_screen = screen;
    m_row = 0;
    m_col = 0;
    m_max_col = 0;
}

Day17Runner::~Day17Runner()
{
}

int Day17Runner::run()
{
    long value;
    int rc;

    rc=m_inputs->getNext(&value);
        
    if (rc != SUCCESS)
    {
        m_terminated=true;
        return SUCCESS;
    }
    
    if (value==10)
    {
        m_row++;
        m_col=0;
    }
    else
    {
        if (m_col > m_max_col)
            m_max_col=m_col;
        m_screen->set(m_row, m_col, Tile((char)value));
        m_col++;
    }
        
    return INPUT_WAIT;
}

int Day17Runner::getRow()
{
    if (m_col==0)
        return m_row-1;
    else
        return m_row;
}

int Day17Runner::getCol()
{
    return m_max_col;
}
