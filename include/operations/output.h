#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "operation.h"
#include "memory.h"

class Output : public Operation
{
public:
    Output();
    ~Output();
    int performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs);
};

#endif
