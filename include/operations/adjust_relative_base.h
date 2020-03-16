#ifndef __ADJUST_RELATIVE_BASE_H__
#define __ADJUST_RELATIVE_BASE_H__

#include "operation.h"
#include "memory.h"

class AdjustRelativeBase : public Operation
{
public:
    AdjustRelativeBase();
    ~AdjustRelativeBase();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs);
};

#endif
