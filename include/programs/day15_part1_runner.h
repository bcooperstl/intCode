#ifndef __DAY15_RUNNER_H__
#define __DAY15_RUNNER_H__

#include <vector>

#include "runner.h"
#include "day15_point.h"
#include "day15_area.h"
#include "inputter_outputter.h"

class Day15Part1Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    Area * m_area;
    int m_droid_x;
    int m_droid_y;
    bool m_first_iteration;
    int m_iteration_count;
    int m_move_outputs;
    int m_check_backup_outputs;
    Point * m_current_checking_point;
    bool m_last_checked;
    Direction m_last_checked_direction;
    void handleLastCheckedResult(int res);
    void setUpNextCheck(Point * checkingPoint);
public:
    Day15Part1Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Area * area);
    ~Day15Part1Runner();
    int getDroidX();
    int getDroidY();
    int run();
};

#endif
