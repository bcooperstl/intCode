#ifndef __PROGRAM_MANAGER_H__
#define __PROGRAM_MANAGER_H__

#include <vector>

#include "program_runner.h"

class ProgramManager
{
private:
    std::vector<ProgramRunner *> m_programs;
public:
    ProgramManager();
    ~ProgramManager();
    void addProgramRunner(ProgramRunner * runner);
    int runPrograms();
    bool isAllTerminated();
};

#endif
