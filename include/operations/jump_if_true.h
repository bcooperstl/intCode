#ifndef __JUMP_IF_TRUE_H__
#define __JUMP_IF_TRUE_H__

#include "operation.h"
#include "memory.h"

class JumpIfTrue : public Operation
{
public:
    JumpIfTrue();
    ~JumpIfTrue();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs);
};

#endif
