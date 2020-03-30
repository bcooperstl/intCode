#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day13_part2_runner.h"
#include "runner.h"

Day13Part2Runner::Day13Part2Runner(std::string name, InputterOutputter * inputs,  InputterOutputter * outputs, Screen * screen, SegmentDisplay * display, Joystick * joystick):Runner(name)
{
    m_inputs = inputs;
    m_outputs = outputs;
    m_screen = screen;
    m_score = display;
    m_joystick = joystick;
}

Day13Part2Runner::~Day13Part2Runner()
{
}

int Day13Part2Runner::run()
{
    long row, col, tileId;
    int rc1, rc2, rc3;
    int operationCount=0;
    while (m_inputs->hasAvailableElements())
    {
        operationCount++;
        rc1=m_inputs->getNext(&col);
        rc2=m_inputs->getNext(&row);
        rc3=m_inputs->getNext(&tileId);
        
        if (col==-1 && row==0) // if the column value is -1 and the row is 0, this should set the score to the third (tileId) Value;
        {
            m_score->setValue(tileId);
        }
        else
        {
            char tileValue=getTileValue(tileId);
            m_screen->set(row, col, Tile(tileValue));
        }    
    }
    std::cout << "My logic performed " << operationCount << " operations" << std::endl;
    display(std::cout);

    if (!operationCount)
    {
        m_terminated=true;
        return SUCCESS;
    }
    else
    {
        int ballColumn, ballRow, paddleColumn, paddleRow;
        findTileAndBall(ballColumn, ballRow, paddleColumn, paddleRow);
        determineJoystickPosition(ballColumn, ballRow, paddleColumn, paddleRow);
        m_outputs->add((long)m_joystick->getPosition());
    }
    
    return INPUT_WAIT;
}

void Day13Part2Runner::display(std::ostream & out)
{
    m_score->display(out);
    m_screen->display(out);
}

void Day13Part2Runner::determineJoystickPosition(int ballColumn, int ballRow, int paddleColumn, int paddleRow)
{
    if (ballColumn == paddleColumn)
        m_joystick->setPosition(neutral);
    else if (ballColumn < paddleColumn) // need to move paddle left
        m_joystick->setPosition(left);
    else
        m_joystick->setPosition(right);
}

void Day13Part2Runner::findTileAndBall(int & ballColumn, int & ballRow, int & paddleColumn, int & paddleRow)
{
    Tile * tmp;
    for (int i=0; i<m_screen->getNumRows(); i++)
    {
        for (int j=0; j<m_screen->getNumCols(); j++)
        {
            m_screen->getTile(i,j,&tmp);
            if (tmp->getValue()=='_')
            {
                paddleRow=i;
                paddleColumn=j;
            }
            else if (tmp->getValue()=='o')
            {
                ballRow=i;
                ballColumn=j;
            }
        }
    }
}

char Day13Part2Runner::getTileValue(int input)
{
    switch (input)
    {
        case 0:
            return ' ';
        case 1:
            return '#';
        case 2:
            return 'x';
        case 3:
            return '_';
        case 4:
            return 'o';
    }
    return '*';
}
