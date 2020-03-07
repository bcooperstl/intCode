#include <cstring>
#include <iostream>
#include <map>

#include "operation.h"
#include "operations_manager.h"
#include "addition.h"
#include "multiplication.h"
#include "input.h"
#include "output.h"
#include "jump_if_true.h"
#include "jump_if_false.h"
#include "less_than.h"
#include "equals.h"

OperationsManager * OperationsManager::m_instance = NULL;

OperationsManager::OperationsManager()
{
    clearAllOperations();
    loadAllOperations();
}

OperationsManager::~OperationsManager()
{
    clearAllOperations();
}

OperationsManager * OperationsManager::getInstance()
{
    if (m_instance == NULL)
    {
        m_instance = new OperationsManager();
    }
    return m_instance;
}

void OperationsManager::loadAllOperations()
{
    Addition * addition = new Addition();
    m_operations.insert(std::pair<int, Operation *>(addition->getOpcode(), addition));
    Multiplication * multiplication = new Multiplication();
    m_operations.insert(std::pair<int, Operation *>(multiplication->getOpcode(), multiplication));
    Input * input = new Input();
    m_operations.insert(std::pair<int, Operation *>(input->getOpcode(), input));
    Output * output = new Output();
    m_operations.insert(std::pair<int, Operation *>(output->getOpcode(), output));
    JumpIfTrue * jumpIfTrue = new JumpIfTrue();
    m_operations.insert(std::pair<int, Operation *>(jumpIfTrue->getOpcode(), jumpIfTrue));
    JumpIfFalse * jumpIfFalse = new JumpIfFalse();
    m_operations.insert(std::pair<int, Operation *>(jumpIfFalse->getOpcode(), jumpIfFalse));
    LessThan * lessThan = new LessThan();
    m_operations.insert(std::pair<int, Operation *>(lessThan->getOpcode(), lessThan));
    Equals * equals = new Equals();
    m_operations.insert(std::pair<int, Operation *>(equals->getOpcode(), equals));
}

void OperationsManager::clearAllOperations()
{
    for (std::map<int, Operation *>::iterator iter=m_operations.begin(); iter!=m_operations.end(); ++iter)
    {
        delete iter->second;
    }
    m_operations.clear();
}

Operation * OperationsManager::getOperation(int opcode)
{
    std::map<int, Operation *>::iterator item = m_operations.find(opcode);
    if (item == m_operations.end())
        return NULL;
    
    return item->second;
}

void OperationsManager::dump(std::ostream & out)
{
    out << "Operations Manager has " << m_operations.size() << " operations:" << std::endl;
    for (std::map<int, Operation *>::iterator iter=m_operations.begin(); iter!=m_operations.end(); ++iter)
    {
        out << "Opcode " << iter->first << " maps to " << iter->second->getName() << std::endl;
    }
}
