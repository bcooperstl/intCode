#ifndef __DAY13_PART2_RUNNER_H__
#define __DAY13_PART2_RUNNER_H__

#include <string>
#include <iostream>

#include "runner.h"
#include "screen.h"
#include "segment_display.h"
#include "joystick.h"
#include "inputter_outputter.h"

class Day13Part2Runner : public Runner
{
private:
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    Screen * m_screen;
    SegmentDisplay * m_score;
    Joystick * m_joystick;
public:
    char getTileValue(int input);
    Day13Part2Runner(std::string name, InputterOutputter * inputs,  InputterOutputter * outputs, Screen * screen, SegmentDisplay * display, Joystick * joystick);
    ~Day13Part2Runner();
    int run();
    void display(std::ostream & out);
    void findTileAndBall(int & ballColumn, int & ballRow, int & paddleColumn, int & paddleRow);
    void determineJoystickPosition(int ballColumn, int ballRow, int paddleColumn, int paddleRow);
};

#endif
