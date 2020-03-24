#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day11_part1_runner.h"
#include "runner.h"

Day11Part1Runner::Day11Part1Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Side * side):Runner(name)
{
    m_inputs = inputs;
    m_outputs = outputs;
    m_side=side;
    m_first_iteration=true;
}

Day11Part1Runner::~Day11Part1Runner()
{
}

int Day11Part1Runner::run()
{
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
