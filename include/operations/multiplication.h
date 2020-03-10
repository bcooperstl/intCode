#ifndef __MULTIPLICATION_H__
#define __MULTIPLICATION_H__

#include "operation.h"
#include "memory.h"

class Multiplication : public Operation
{
public:
    Multiplication();
    ~Multiplication();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs);
};

#endif
