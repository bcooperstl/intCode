#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day17_part2_runner.h"
#include "runner.h"

Day17Part2Runner::Day17Part2Runner(std::string name, InputterOutputter * inputs, Screen * screen):Runner(name)
{
    m_inputs = inputs;
    m_screen = screen;
    m_row = 0;
    m_col = 0;
    m_max_col = 0;
    m_final_value = 0;
}

Day17Part2Runner::~Day17Part2Runner()
{
}

int Day17Part2Runner::run()
{
    long value;
    int rc;

    rc=m_inputs->getNext(&value);
        
    if (rc != SUCCESS)
    {
        m_terminated=true;
        return SUCCESS;
    }
    
    if (value > 255)
    {
        m_final_value=value;
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

int Day17Part2Runner::getRow()
{
    if (m_col==0)
        return m_row-1;
    else
        return m_row;
}

int Day17Part2Runner::getCol()
{
    return m_max_col;
}

int Day17Part2Runner::getFinalValue()
{
    return m_final_value;
}
