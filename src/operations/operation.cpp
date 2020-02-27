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

