#ifndef __PROGRAM_RUNNER_H__
#define __PROGRAM_RUNNER_H__

#include <string>

#include "memory.h"
#include "operation.h"
#include "operations_manager.h"
#include "runner.h"

class ProgramRunner : public Runner
{
private:
    Memory * m_memory;
    int m_ip;
    OperationsManager * m_operations_manager;
    InputterOutputter * m_inputs;
    InputterOutputter * m_outputs;
    void init(Memory * memory, std::string name);
public:
    ProgramRunner(Memory * memory, std::string name);
    ProgramRunner(Memory * memory);
    ~ProgramRunner();
    int run();
    void setInputs(InputterOutputter * inputs);
    void setOutputs(InputterOutputter * outputs);
};

#endif
