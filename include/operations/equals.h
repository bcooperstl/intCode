#ifndef __EQUALS_H__
#define __EQUALS_H__

#include "operation.h"
#include "memory.h"

class Equals : public Operation
{
public:
    Equals();
    ~Equals();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs);
};

#endif
