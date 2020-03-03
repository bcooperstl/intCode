#include <cstring>

#include "operation.h"

Operation::Operation(std::string name, int opcode)
{
    m_name = name;
    m_opcode = opcode;
}

Operation::~Operation()
{
}

std::string Operation::getName()
{
    return m_name;
}

int Operation::getOpcode()
{
    return m_opcode;
}

int Operation::getMemoryModeForParameter(int ip, int parmNumber)
{
    if (parmNumber == 1)
        return (ip / 100)%10;
    else if (parmNumber == 2)
        return (ip / 1000)%10;
    else if (parmNumber == 3)
        return (ip / 10000)%10;
    return -1;
}
