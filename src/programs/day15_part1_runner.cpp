#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "day15_part1_runner.h"
#include "runner.h"

Day15Part1Runner::Day15Part1Runner(std::string name, InputterOutputter * inputs, InputterOutputter * outputs, Area * area):Runner(name)
{
    m_inputs = inputs;
    m_outputs = outputs;
    m_area=area;
    m_droid_x=0;
    m_droid_y=0;
    m_first_iteration=true;
    m_iteration_count=0;
    m_move_outputs=0;
    m_current_checking_point=NULL;
    m_last_checked=false;
}

Day15Part1Runner::~Day15Part1Runner()
{
}

int Day15Part1Runner::getDroidX()
{
    return m_droid_x;
}

int Day15Part1Runner::getDroidY()
{
    return m_droid_y;
}

void Day15Part1Runner::handleLastCheckedResult(int res)
{
    int moveX=m_droid_x;
    int moveY=m_droid_y;
    Direction backupDirection;
    switch (m_last_checked_direction)
    {
        case North:
            moveY++;
            backupDirection=South;
            break;
        case South:
            moveY--;
            backupDirection=North;
            break;
        case East:
            moveX++;
            backupDirection=West;
            break;
        case West:
            moveX--;
            backupDirection=East;
            break;
    }
    bool backItUp=false;
    Point * newPoint;
    switch (res)
    {
        case 0: // wall - no need to move. Just need to record the wall
#ifdef DEBUG_PROGRAMS
            std::cerr << "Wall detected at (" << moveX << "," << moveY << ")." << std::endl;
#endif
            newPoint = new Point(moveX, moveY, m_current_checking_point, m_last_checked_direction);
            newPoint->setContents(Wall);
            m_area->addPoint(newPoint);
            break;
        case 1: // walking area - need to record this point as well as schedule a backtrack
#ifdef DEBUG_PROGRAMS
            std::cerr << "Open space detected (" << moveX << "," << moveY << ")." << std::endl;
#endif
            newPoint = new Point(moveX, moveY, m_current_checking_point, m_last_checked_direction);
            newPoint->setContents(WalkingArea);
            m_area->addPoint(newPoint);
            backItUp=true;
            break;
        case 2: // oxygen - need to record this point as well as schedule a backtrack
#ifdef DEBUG_PROGRAMS
            std::cerr << "**Oxygen Sensor detected (" << moveX << "," << moveY << ")." << std::endl;
#endif
            newPoint = new Point(moveX, moveY, m_current_checking_point, m_last_checked_direction);
            newPoint->setContents(OxygenSensor);
            m_area->addPoint(newPoint);
            backItUp=true;
            break;
    }
    if (backItUp)
    {
#ifdef DEBUG_PROGRAMS
        std::cerr << "Setting a move backward (" << backupDirection << ") to return the droid to (" << m_droid_x << "," << m_droid_y << ")" << std::endl;
        std::cerr << "Adding " << backupDirection << " to intCode inputs" << std::endl;
#endif
        m_check_backup_outputs=1;
        m_outputs->add(backupDirection);
    }
}

void Day15Part1Runner::setUpNextCheck(Point * checkingPoint)
{
    bool shouldScheduleMove=false;
    Direction moveDirection;
    
    if (!m_last_checked) // setting up for first check - north
    {
        // Move to this point
        std::vector<Direction> path_to_point = checkingPoint->getPathToHere();
#ifdef DEBUG_PROGRAMS
        std::cerr << "Moving " << path_to_point.size() << " steps to (" << checkingPoint->getX() << "," << checkingPoint->getY() << ")" << std::endl;
#endif
        for (int i=0; i<path_to_point.size(); i++)
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Adding " << path_to_point[i] << " to intCode inputs" << std::endl;
#endif
            m_outputs->add(path_to_point[i]);
        }
        m_move_outputs+=path_to_point.size();
        m_droid_x=checkingPoint->getX();
        m_droid_y=checkingPoint->getY();

        int northX=m_droid_x;
        int northY=m_droid_y+1;
        Point * northPoint=m_area->getPoint(northX, northY);
        m_last_checked_direction=North;
        if (northPoint != NULL)
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Not checking north - point (" << northX << "," << northY << ") already explored" << std::endl;
#endif
        }
        else
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Need to check north point at (" << northX << "," << northY << ")" << std::endl;
#endif
            shouldScheduleMove=true;
            moveDirection=North;
        }
    }
    
    if (!shouldScheduleMove && m_last_checked_direction==North) // last move was north. now check south
    {
        int southX=m_droid_x;
        int southY=m_droid_y-1;
        Point * southPoint=m_area->getPoint(southX, southY);
        m_last_checked_direction=South;
        if (southPoint != NULL)
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Not checking south - point (" << southX << "," << southY << ") already explored" << std::endl;
#endif
        }
        else
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Need to check south point at (" << southX << "," << southY << ")" << std::endl;
#endif
            shouldScheduleMove=true;
            moveDirection=South;
        }
    }
    
    if (!shouldScheduleMove && m_last_checked_direction==South) // last move was south. now check east
    {
        int eastX=m_droid_x+1;
        int eastY=m_droid_y;
        Point * eastPoint=m_area->getPoint(eastX, eastY);
        m_last_checked_direction=East;
        if (eastPoint != NULL)
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Not checking east - point (" << eastX << "," << eastY << ") already explored" << std::endl;
#endif
        }
        else
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Need to check east point at (" << eastX << "," << eastY << ")" << std::endl;
#endif
            shouldScheduleMove=true;
            moveDirection=East;
        }
    }
    
    if (!shouldScheduleMove && m_last_checked_direction==East) // last move was east. now check west
    {
        int westX=m_droid_x-1;
        int westY=m_droid_y;
        Point * westPoint=m_area->getPoint(westX, westY);
        m_last_checked_direction=West;
        if (westPoint != NULL)
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Not checking west - point (" << westX << "," << westY << ") already explored" << std::endl;
#endif
        }
        else
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Need to check west point at (" << westX << "," << westY << ")" << std::endl;
#endif
            shouldScheduleMove=true;
            moveDirection=West;
        }
    }
    
    if (shouldScheduleMove)
    {
        m_current_checking_point=checkingPoint;
        m_last_checked=true;
        m_last_checked_direction=moveDirection;
#ifdef DEBUG_PROGRAMS
        std::cerr << "Adding " << moveDirection << " to intCode inputs" << std::endl;
#endif
        m_outputs->add(moveDirection);
    }
    else
    {
        // good to go home
        std::vector<Direction> path_to_point = checkingPoint->getPathToHome();
#ifdef DEBUG_PROGRAMS
        std::cerr << "Returning " << path_to_point.size() << " steps to (0,0)" << std::endl;
#endif
        for (int i=0; i<path_to_point.size(); i++)
        {
#ifdef DEBUG_PROGRAMS
            std::cerr << "Adding " << path_to_point[i] << " to intCode inputs" << std::endl;
#endif
            m_outputs->add(path_to_point[i]);
        }
        m_move_outputs+=path_to_point.size();
        m_droid_x=0;
        m_droid_y=0;
        m_area->removeExploredPoint(checkingPoint);
        m_current_checking_point=NULL;
        m_last_checked=false;
    }
}

int Day15Part1Runner::run()
{
#ifdef DEBUG_PROGRAMS
    if (m_iteration_count++%100==0)
        m_area->display(std::cout, m_droid_x, m_droid_y);
#endif
    
    if (m_check_backup_outputs == 1)
    {
        // There was a command to move the droid back after a successful check. This should return 1 or 2
#ifdef DEBUG_PROGRAMS
        std::cerr << "Pulling out the output for going back one space" << std::endl;
#endif
        
        long tmp;
        int rc;
        rc=m_inputs->getNext(&tmp);
#ifdef DEBUG_PROGRAMS
        std::cerr << "Received " << tmp << " from intcode outputs" << std::endl;
#endif
        if (rc!=SUCCESS)
        {
            std::cerr << "**** Error on back up - retriveal error " << rc << std::endl;
            exit(1);
        }
        if (tmp==0)
        {
            std::cerr << "**** Error on back up - hit a wall going back" << std::endl;
            exit(1);
        }
    }
    m_check_backup_outputs=0;
    
    if (m_move_outputs > 0)
    {
        // the last set of commands were a list of moves to the droid. Need to get all of their outputs.
#ifdef DEBUG_PROGRAMS
        std::cerr << "Going through " << m_move_outputs << " move out steps first" << std::endl;
#endif
        for (int i=0; i<m_move_outputs; i++)
        {
            long tmp;
            int rc;
            rc=m_inputs->getNext(&tmp);
#ifdef DEBUG_PROGRAMS
            std::cerr << "Received " << tmp << " from intcode outputs" << std::endl;
#endif
            if (rc!=SUCCESS)
            {
                std::cerr << "**** Error on iteration " << i << " - retriveal error " << rc << std::endl;
                exit(1);
            }
            if (tmp==0)
            {
                std::cerr << "**** Error on iteration " << i << " - hit a wall going back to start" << std::endl;
                exit(1);
            }
        }
#ifdef DEBUG_PROGRAMS
        std::cerr << "Droid has consumed " << m_move_outputs << " steps" << std::endl;
#endif
        m_move_outputs=0;
    }
    
    if (m_last_checked==true)
    {
        long res;
        int rc;
        rc=m_inputs->getNext(&res);
#ifdef DEBUG_PROGRAMS
        std::cerr << "Received " << res << " from intcode outputs" << std::endl;
#endif
        if (rc!=SUCCESS)
        {
            std::cerr << "**** Error on last checked - retriveal error " << rc << std::endl;
            exit(1);
        }
        handleLastCheckedResult(res);
        setUpNextCheck(m_current_checking_point);
    }
    
    if (m_move_outputs==0 && !m_last_checked)
    {
        Point * nextPoint = m_area->getNextPointToExplore();
        if (nextPoint)
            setUpNextCheck(nextPoint);
    }
    
    if (m_move_outputs==0 && m_area->getNextPointToExplore() == NULL)
    {
        m_terminated=true;
    }
    
    return SUCCESS;
}
