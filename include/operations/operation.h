#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <cstring>
#include "memory.h"

class Operation
{
private:
    std::string m_name;
    int m_opcode;
public:
    Operation(std::string name, int opcode);
    ~Operation();
    virtual int performOperation(Memory * m, long ip) = 0;
    virtual int getIPIncrement() = 0;
    std::string getName();
    int getOpcode();
    int getMemoryModeForParameter(int ip, int parmNumber);
};

#endif
