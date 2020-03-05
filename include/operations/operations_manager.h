#ifndef __OPERATIONS_MANAGER_H__
#define __OPERATIONS_MANAGER_H__

#include <iostream>
#include <map>
#include "operation.h"

class OperationsManager
{
private:
    std::map<int, Operation *> m_operations; // map from opcode to operation
    OperationsManager * m_operations_manager = NULL;
    void loadAllOperations();
    void clearAllOperations();
    OperationsManager();
public:
    ~OperationsManager();
    OperationsManager * getOperationsManager();
    Operation * getOperation(int opcode);
    void dump(std::ostream & out);
};

#endif
