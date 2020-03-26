#ifndef __DAY11_PART1_RUNNER_H__
#define __DAY11_PART1_RUNNER_H__

#include <string>

#include "runner.h"
#include "day11_side.h"
#include "inputter_outputter.h"

class Day11Part1Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    Side * m_side;
    bool m_first_iteration;
public:
    Day11Part1Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Side * side);
    ~Day11Part1Runner();
    int run();
};

#endif
