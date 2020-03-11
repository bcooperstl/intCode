#ifndef __PROGRAM_RUNNER_H__
#define __PROGRAM_RUNNER_H__

#include <string>

#include "memory.h"
#include "operation.h"
#include "operations_manager.h"

class ProgramRunner
{
private:
    Memory * m_memory;
    int m_ip;
    bool m_terminated;
    OperationsManager * m_operations_manager;
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    std::string m_name;
    void init(Memory * memory, std::string name);
public:
    ProgramRunner(Memory * memory, std::string name);
    ProgramRunner(Memory * memory);
    ~ProgramRunner();
    int run();
    void setInputs(InputterOutputter * inputs);
    void setOutputs(InputterOutputter * outputs);
    bool isTerminated();
    std::string getName();
};

#endif
