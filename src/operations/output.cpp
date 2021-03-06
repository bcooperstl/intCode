#include <cstring>
#include <iostream>

#include "output.h"
#include "memory.h"

static std::string NAME="Output";
static int OPCODE=4;
static int IP_INCREMENT=2;

Output::Output() : Operation(NAME, OPCODE)
{
}

Output::~Output()
{
}

int Output::performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs)
{
    long val, res;
    res = m->get(ip+1, getMemoryModeForParameter(opcode, 1), &val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val from position " << ip+1 << std::endl;
        return res;
    }
    
#ifdef DEBUG_OPERATIONS
    std::cerr << getName() << ": at instruction pointer " << ip << " with opcode " << opcode << std::endl;
    std::cerr << "   parm 1 - memory mode " << getMemoryModeForParameter(opcode, 1) << " got a value of " << val << " for val" << std::endl;
#endif

    if (outputs == NULL)
    {
        std::cout << "***Output: " << val << std::endl;
    }
    else
    {
        outputs->add(val);
    }

    *new_ip = ip+IP_INCREMENT;

#ifdef DEBUG_OPERATIONS
    std::cerr << "   outputted output value of " << val << std::endl;
    std::cerr << "   next instruction pointer incremented by " << IP_INCREMENT << " to " << *new_ip << std::endl;
#endif

    return SUCCESS;
}
