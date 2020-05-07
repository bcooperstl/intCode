#ifndef __DAY23_PART1_RUNNER_H__
#define __DAY23_PART1_RUNNER_H__

#include <string>

#include "runner.h"
#include "screen.h"
#include "inputter_outputter.h"

#define NUM_NICS 50

class Day23Part1Runner : public Runner
{
private:
    InputterOutputter * m_to_nics[NUM_NICS];
    InputterOutputter * m_from_nics[NUM_NICS];
    int m_first_y_to_255;
public:
    Day23Part1Runner(std::string name);
    ~Day23Part1Runner();
    int run();
    void addNic(int number, InputterOutputter * to_nic, InputterOutputter * from_nic);
    int getFirstYTo255();
};

#endif
