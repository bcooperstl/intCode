#include <iostream>
#include <cstring>

#include "constants.h"
#include "memory.h"
#include "addition.h"
#include "multiplication.h"
#include "program_runner.h"
#include "operation.h"

static const int HALT_OPCODE=99;

ProgramRunner::ProgramRunner(Memory * memory)
{
    m_memory = memory;
    m_ip = 0;
    m_addition = new Addition();
    m_multiplication = new Multiplication();
}

ProgramRunner::~ProgramRunner()
{
    delete m_addition;
    delete m_multiplication;
}

int ProgramRunner::run()
{
    bool halt_reached = false;
    int res = SUCCESS;
    while((!halt_reached) && m_ip <= m_memory->getSize())
    {
        int opcode, ip_increment=0;
        res = m_memory->get(m_ip, &opcode);

        if (res != SUCCESS)
        {
            std::cerr << "Error reached reading opcode at memory location " << m_ip << std::endl;
            return res;
        }

        res = SUCCESS;
        if (opcode == m_addition->getOpcode())
        {
            res = m_addition->performOperation(m_memory, m_ip);
            ip_increment=m_addition->getIPIncrement();
        }
        else if (opcode == m_multiplication->getOpcode())
        {
            res = m_multiplication->performOperation(m_memory, m_ip);
            ip_increment=m_multiplication->getIPIncrement();
        }
        else if (opcode == HALT_OPCODE)
        {
            halt_reached = true;
        }
        else
        {
            std::cerr << "Invalid opcode " << opcode << " found at memory location " << m_ip << std::endl;
            return ERR_INVALID_OPCODE;
        }
        
        if (res != SUCCESS)
        {
            std::cerr << "Error reached on opcode " << opcode << " at memory location " << m_ip << std::endl;
            return res;
        }
        m_ip+=ip_increment;
    }
    return SUCCESS;
}
