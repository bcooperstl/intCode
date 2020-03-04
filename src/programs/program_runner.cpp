#include <iostream>
#include <cstring>

#include "constants.h"
#include "memory.h"
#include "addition.h"
#include "input.h"
#include "output.h"
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
    m_input = new Input();
    m_output = new Output();
}

ProgramRunner::~ProgramRunner()
{
    delete m_addition;
    delete m_multiplication;
    delete m_input;
    delete m_output;
}

int ProgramRunner::run()
{
    bool halt_reached = false;
    int res = SUCCESS;
    while((!halt_reached) && m_ip <= m_memory->getSize())
    {
        int opcode, ip_increment=0;
        res = m_memory->getImmediateMode(m_ip, &opcode);

        if (res != SUCCESS)
        {
            std::cerr << "Error reached reading opcode at memory location " << m_ip << std::endl;
            return res;
        }

        res = SUCCESS;
        
        int modelessOpcode = opcode % 100;
        
        if (modelessOpcode == m_addition->getOpcode())
        {
            res = m_addition->performOperation(m_memory, m_ip);
            ip_increment=m_addition->getIPIncrement();
        }
        else if (modelessOpcode == m_multiplication->getOpcode())
        {
            res = m_multiplication->performOperation(m_memory, m_ip);
            ip_increment=m_multiplication->getIPIncrement();
        }
        else if (modelessOpcode == m_input->getOpcode())
        {
            res = m_input->performOperation(m_memory, m_ip);
            ip_increment=m_input->getIPIncrement();
        }
        else if (modelessOpcode == m_output->getOpcode())
        {
            res = m_output->performOperation(m_memory, m_ip);
            ip_increment=m_output->getIPIncrement();
        }
        else if (modelessOpcode == HALT_OPCODE)
        {
            halt_reached = true;
        }
        else
        {
            std::cerr << "Invalid opcode " << modelessOpcode << " via " << opcode << " found at memory location " << m_ip << std::endl;
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
