#ifndef __DAY17_RUNNER_H__
#define __DAY17_RUNNER_H__

#include <string>

#include "runner.h"
#include "screen.h"
#include "inputter_outputter.h"

class Day17Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    Screen * m_screen;
    int m_row;
    int m_col;
    int m_max_col;
public:
    Day17Runner(std::string name, InputterOutputter * inputs,  Screen * screen);
    ~Day17Runner();
    int run();
    int getRow();
    int getCol();
};

#endif
