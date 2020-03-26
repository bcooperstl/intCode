#ifndef __DAY11_PART1_RUNNER_H__
#define __DAY11_PART1_RUNNER_H__

#include <string>

#include "runner.h"
#include "day11_side.h"
#include "inputter_outputter.h"

class Day11Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    Side * m_side;
    bool m_first_iteration;
    int m_iteration_count;
public:
    Day11Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Side * side);
    ~Day11Runner();
    int run();
};

#endif
