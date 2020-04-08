#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day15_part1_runner.h"
#include "runner.h"

Day15Part1Runner::Day15Part1Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Area * area):Runner(name)
{
    m_inputs = inputs;
    m_outputs = outputs;
    m_area=area;
    m_droid_x=0;
    m_droid_y=0;
    m_first_iteration=true;
    m_iteration_count=0;
}

Day15Part1Runner::~Day15Part1Runner()
{
}

int Day15Part1Runner::getDroidX()
{
    return m_droid_x;
}

int Day15Part1Runner::getDroidY()
{
    return m_droid_y;
}

int Day15Part1Runner::run()
{
    if (m_move_queue.empty() && m_check_queue.empty())
    {
        m_terminated=true;
    }
    
    return SUCCESS;
}
