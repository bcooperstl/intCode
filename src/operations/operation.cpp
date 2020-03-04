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
    int divisor = 1;
    if (parmNumber == 1)
        divisor = 100;
    else if (parmNumber == 2)
        divisor = 1000;
    else if (parmNumber == 3)
        divisor = 10000;

    int mode = (ip / divisor)%10;

    return mode;
}
