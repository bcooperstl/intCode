#ifndef __LESS_THAN_H__
#define __LESS_THAN_H__

#include "operation.h"
#include "memory.h"

class LessThan : public Operation
{
public:
    LessThan();
    ~LessThan();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs);
};

#endif
