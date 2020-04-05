#ifndef __DAY15_RUNNER_H__
#define __DAY15_RUNNER_H__

#include <vector>

#include "runner.h"
#include "day15_point.h"
#include "day15_area.h"
#include "inputter_outputter.h"

class Day15Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    Area * m_area;
    int m_droid_x;
    int m_droid_y;
    bool m_first_iteration;
    int m_iteration_count;
    std::vector<Direction> m_move_queue;
    std::vector<Direction> m_check_queue;
    Direction m_
public:
    Day15Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Area * area);
    ~Day15Runner();
    int getDroidX();
    int getDroidY();
    int run();
};

#endif
