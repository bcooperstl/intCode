#ifndef __INPUT_H__
#define __INPUT_H__

#include "operation.h"
#include "memory.h"

class Input : public Operation
{
public:
    Input();
    ~Input();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip);
};

#endif
