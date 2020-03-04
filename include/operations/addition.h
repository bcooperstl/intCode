#ifndef __ADDITION_H__
#define __ADDITION_H__

#include "operation.h"
#include "memory.h"

class Addition : public Operation
{
public:
    Addition();
    ~Addition();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip);
};

#endif
