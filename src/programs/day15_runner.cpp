#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day15_runner.h"
#include "runner.h"

Day15Runner::Day15Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Area * area):Runner(name)
{
    m_inputs = inputs;
    m_outputs = outputs;
    m_area=area;
    m_droid_x=0;
    m_droid_y=0;
    m_first_iteration=true;
    m_iteration_count=0;
}

Day15Runner::~Day15Runner()
{
}

int Day15Runner::getDroidX()
{
    return m_droid_x;
}

int Day15Runner::getDroidY()
{
    return m_droid_y;
}

int Day15Runner::run()
{
    if (m_iteration_count%1000==0)
    {
        std::cout << "Iteration " << m_iteration_count << std::endl;
        m_side->dump(std::cout);
    }
    m_iteration_count++;
    long colorValue, directionValue;
    int rc1, rc2;
    if (!m_first_iteration)
    {
        // need to get two input values. If these are not present, assume the other program has completed and set this program to terminated.
        // for this reason, must skip this portion on the first time through
        rc1=m_inputs->getNext(&colorValue);
        rc2=m_inputs->getNext(&directionValue);
        if (rc1 != SUCCESS && rc2 != SUCCESS)
        {
            m_terminated=true;
            return SUCCESS;
        }
        PanelColor color;
        if (colorValue == 0)
        {
            color=black;
        }
        else if (colorValue == 1)
        {
            color=white;
        }
        else
        {
            std::cerr << "Invalid color value " << colorValue << " received" << std::endl;
            return ERR_UNKNOWN;
        }
        m_side->paint(color);

        TurnDirection turn;
        if (directionValue == 0)
        {
            turn=left;
        }
        else if (directionValue == 1)
        {
            turn=right;
        }
        else
        {
            std::cerr << "Invalid direction value " << directionValue << " received" << std::endl;
            return ERR_UNKNOWN;
        }
        m_side->turnAndMove(turn);
    }
    
    m_first_iteration=false;
    
    PanelColor currentColor = m_side->getCurrentPanelColor();
    std::cerr << "Current color of is " << m_side->getCurrentPanelColor() << std::endl;
    if (currentColor==black)
    {
        m_outputs->add(0);
    }
    else
    {
        m_outputs->add(1);
    }
    return INPUT_WAIT;
}
