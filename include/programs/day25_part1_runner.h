#ifndef __DAY25_PART1_RUNNER_H__
#define __DAY25_PART1_RUNNER_H__

#include <string>

#include "runner.h"
#include "ascii_inputter_outputter.h"

class Day25Part1Runner : public Runner
{
private:
    AsciiInputterOutputter * m_from_intcode;
    AsciiInputterOutputter * m_to_intcode;
    std::string m_program_steps[50];
    std::string m_items[8];
    int m_program_step_position;
    int m_permutation;
    bool m_found_it;
public:
    Day25Part1Runner(std::string name, AsciiInputterOutputter * fromIntcode,  AsciiInputterOutputter * toIntcode);
    ~Day25Part1Runner();
    int run();
};

#endif
