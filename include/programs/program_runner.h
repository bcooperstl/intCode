#ifndef __PROGRAM_RUNNER_H__
#define __PROGRAM_RUNNER_H__

#include "memory.h"
#include "operation.h"

class ProgramRunner
{
private:
    Memory * m_memory;
    int m_ip;
    Operation * m_addition;
    Operation * m_multiplication;
    Operation * m_input;
    Operation * m_output;
public:
    ProgramRunner(Memory * memory);
    ~ProgramRunner();
    int run();
};

#endif
