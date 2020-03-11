#include <iostream>
#include <cstring>
#include <sstream>

#include "constants.h"
#include "memory.h"
#include "program_runner.h"
#include "operation.h"
#include "operations_manager.h"

static const int HALT_OPCODE=99;

ProgramRunner::ProgramRunner(Memory * memory, std::string name)
{
    init(memory, name);
}

ProgramRunner::ProgramRunner(Memory * memory)
{
    std::stringstream nameStream;
    nameStream << "noName" << memory;
    init(memory, nameStream.str());
}

void ProgramRunner::init(Memory * memory, std::string name)
{
    m_memory = memory;
    m_ip = 0;
    m_operations_manager=OperationsManager::getInstance();
    m_inputs = NULL;
    m_outputs = NULL;
    m_terminated = false;
    m_name = name;
}

ProgramRunner::~ProgramRunner()
{
}

int ProgramRunner::run()
{
    bool halt_reached = false;
    bool input_wait = false;
    int res = SUCCESS;
    int ret_code = SUCCESS;
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
            m_terminated = true;
            ret_code = SUCCESS;
        }
        else if (operation != NULL)
        {
            res = operation->performOperation(m_memory, m_ip, opcode, &new_ip, m_inputs, m_outputs);
            if (res == INPUT_WAIT) // if waiting for input, break out of this program
            {
                ret_code=INPUT_WAIT;
                break;
            }
        }
        else
        {
            std::cerr << "Invalid opcode " << modelessOpcode << " via " << opcode << " found at memory location " << m_ip << std::endl;
            ret_code=ERR_INVALID_OPCODE;
            break;
        }
        
        if (res != SUCCESS)
        {
            std::cerr << "Error reached on opcode " << opcode << " at memory location " << m_ip << std::endl;
            ret_code=res;
        }
        m_ip=new_ip;
    }
    return ret_code;
}

void ProgramRunner::setInputs(InputterOutputter * inputs)
{
    m_inputs = inputs;
}

void ProgramRunner::setOutputs(InputterOutputter * outputs)
{
    m_outputs = outputs;
}

bool ProgramRunner::isTerminated()
{
    return m_terminated;
}
