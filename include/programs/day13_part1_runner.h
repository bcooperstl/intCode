#ifndef __DAY13_PART1_RUNNER_H__
#define __DAY13_PART1_RUNNER_H__

#include <string>

#include "runner.h"
#include "screen.h"
#include "inputter_outputter.h"

class Day13Part1Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    Screen * m_screen;
public:
    char getTileValue(int input);
    Day13Part1Runner(std::string name, InputterOutputter * inputs,  Screen * screen);
    ~Day13Part1Runner();
    int run();
};

#endif
