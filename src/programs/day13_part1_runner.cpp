#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day13_part1_runner.h"
#include "runner.h"

Day13Part1Runner::Day13Part1Runner(std::string name, InputterOutputter * inputs, Screen * screen):Runner(name)
{
    m_inputs = inputs;
    m_screen = screen;
}

Day13Part1Runner::~Day13Part1Runner()
{
}

int Day13Part1Runner::run()
{
    long row, col, tileId;
    int rc1, rc2, rc3;

    rc1=m_inputs->getNext(&col);
    rc2=m_inputs->getNext(&row);
    rc3=m_inputs->getNext(&tileId);
        
    if (rc1 != SUCCESS && rc2 != SUCCESS && rc3 != SUCCESS)
    {
        m_terminated=true;
        return SUCCESS;
    }
        
    char tileValue=getTileValue(tileId);
    m_screen->set(row, col, Tile(tileValue));
        
    m_screen->display(std::cout);
    
    return INPUT_WAIT;
}

char Day13Part1Runner::getTileValue(int input)
{
    switch (input)
    {
        case 0:
            return ' ';
        case 1:
            return '#';
        case 2:
            return 'x';
        case 3:
            return '_';
        case 4:
            return 'o';
    }
    return '*';
}
