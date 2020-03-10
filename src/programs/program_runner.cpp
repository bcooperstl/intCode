#include <iostream>
#include <cstring>

#include "constants.h"
#include "memory.h"
#include "program_runner.h"
#include "operation.h"
#include "operations_manager.h"

static const int HALT_OPCODE=99;

ProgramRunner::ProgramRunner(Memory * memory)
{
    m_memory = memory;
    m_ip = 0;
    m_operations_manager=OperationsManager::getInstance();
    m_inputs = NULL;
    m_outputs = NULL;
}

ProgramRunner::~ProgramRunner()
{
}

int ProgramRunner::run()
{
    bool halt_reached = false;
    int res = SUCCESS;
    while((!halt_reached) && m_ip <= m_memory->getSize())
    {
        int opcode;
        long new_ip=0;
        res = m_memory->getImmediateMode(m_ip, &opcode);

        if (res != SUCCESS)
        {
            std::cerr << "Error reached reading opcode at memory location " << m_ip << std::endl;
            return res;
        }

        res = SUCCESS;
        
        int modelessOpcode = opcode % 100;
        Operation * operation = m_operations_manager->getOperation(modelessOpcode);
        if (modelessOpcode == HALT_OPCODE)
        {
            halt_reached = true;
        }
        else if (operation != NULL)
        {
            res = operation->performOperation(m_memory, m_ip, opcode, &new_ip, m_inputs, m_outputs);
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
        m_ip=new_ip;
    }
    return SUCCESS;
}

void ProgramRunner::setInputs(InputterOutputter * inputs)
{
    m_inputs = inputs;
}

void ProgramRunner::setOutputs(InputterOutputter * outputs)
{
    m_outputs = outputs;
}

