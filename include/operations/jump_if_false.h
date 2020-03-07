#ifndef __JUMP_IF_FALSE_H__
#define __JUMP_IF_FALSE_H__

#include "operation.h"
#include "memory.h"

class JumpIfFalse : public Operation
{
public:
    JumpIfFalse();
    ~JumpIfFalse();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip);
};

#endif
