#ifndef __PROGRAM_RUNNER_H__
#define __PROGRAM_RUNNER_H__

#include "memory.h"
#include "operation.h"
#include "operations_manager.h"

class ProgramRunner
{
private:
    Memory * m_memory;
    int m_ip;
    OperationsManager * m_operations_manager;
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
public:
    ProgramRunner(Memory * memory);
    ~ProgramRunner();
    int run();
    void setInputs(InputterOutputter * inputs);
    void setOutputs(InputterOutputter * outputs);
};

#endif
