#ifndef __DAY23_PART2_RUNNER_H__
#define __DAY23_PART2_RUNNER_H__

#include <string>

#include "runner.h"
#include "screen.h"
#include "inputter_outputter.h"

#define NUM_NICS 50

class Day23Part2Runner : public Runner
{
private:
    InputterOutputter * m_to_nics[NUM_NICS];
    InputterOutputter * m_from_nics[NUM_NICS];
    int m_nat_x;
    int m_nat_y;
    int m_nat_prior_sent_y;
    bool m_first_run;
public:
    Day23Part2Runner(std::string name);
    ~Day23Part2Runner();
    int run();
    void addNic(int number, InputterOutputter * to_nic, InputterOutputter * from_nic);
    int getFirstDupeNatY();
};

#endif
