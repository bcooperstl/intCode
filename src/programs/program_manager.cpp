#include <iostream>
#include <vector>

#include "program_manager.h"
#include "program_runner.h"

ProgramManager::ProgramManager()
{
    m_programs.clear();
}

ProgramManager::~ProgramManager()
{
    m_programs.clear();
}

void ProgramManager::addProgramRunner(ProgramRunner * program)
{
    m_programs.push_back(program);
}

bool ProgramManager::isAllTerminated()
{
    for (int i=0; i<m_programs.size(); i++)
    {
        if (!m_programs[i]->isTerminated())
        {
            return false;
        }
    }
    return true;
}

int ProgramManager::runPrograms()
{
    int current_program_index = 0, rc;
    while (current_program_index < m_programs.size())
    {
        ProgramRunner * current_program = m_programs[current_program_index];
        std::cerr << "Running program " << current_program_index << " = " << current_program->getName() << std::endl;
        // don't run this program if it is terminated
        if (current_program->isTerminated())
        {
            std::cerr << "  Skipping - program is already terminated" << std::endl;
            continue;
        }
        rc = current_program->run();
        if (rc == SUCCESS)
        {
            if (current_program->isTerminated())
            {
                std::cerr << "   Program ran to completion" << std::endl;
            }
        }
        else if (rc == INPUT_WAIT)
        {
            std::cerr << "   Program is awaiting input" << std::endl;
        }
        else
        {
            std::cerr << "   Error " << rc << " received. " << std::endl;
            break;
        }
        current_program_index++;
        if (current_program_index == m_programs.size())
        {
            // gone through the list make sure not all are terminated. restart at program 0
            if (isAllTerminated())
            {
                std::cerr << "All programs have terminated" << std::endl;
                break;
            }
            current_program_index=0;
        }
    }
    return rc;
}