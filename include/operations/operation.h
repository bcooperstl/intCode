#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <cstring>
#include "memory.h"
#include "inputter_outputter.h"

class Operation
{
private:
    std::string m_name;
    int m_opcode;
public:
    Operation(std::string name, int opcode);
    ~Operation();
    virtual int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs) = 0;
    std::string getName();
    int getOpcode();
    int getMemoryModeForParameter(int ip, int parmNumber);
};

#endif
