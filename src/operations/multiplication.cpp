#include <cstring>
#include <iostream>

#include "multiplication.h"
#include "memory.h"

static std::string NAME="Multiplication";
static int OPCODE=2;
static int IP_INCREMENT=4;

Multiplication::Multiplication() : Operation(NAME, OPCODE)
{
}

Multiplication::~Multiplication()
{
}

int Multiplication::performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs)
{
    long val1, val2, addrDest, product, res;
    res = m->get(ip+1, getMemoryModeForParameter(opcode, 1), &val1);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val1 from position " << ip+1 << std::endl;
        return res;
    }
    res = m->get(ip+2, getMemoryModeForParameter(opcode, 2), &val2);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val2 from position " << ip+2 << std::endl;
        return res;
    }
    res = m->getForWrite(ip+3, getMemoryModeForParameter(opcode, 3), &addrDest);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addrDest from position " << ip+3 << std::endl;
        return res;
    }

#ifdef DEBUG_OPERATIONS
    std::cerr << getName() << ": at instruction pointer " << ip << " with opcode " << opcode << std::endl;
    std::cerr << "   parm 1 - memory mode " << getMemoryModeForParameter(opcode, 1) << " got a value of " << val1 << " for val1" << std::endl;
    std::cerr << "   parm 2 - memory mode " << getMemoryModeForParameter(opcode, 2) << " got a value of " << val2 << " for val2" << std::endl;
    std::cerr << "   parm 3 - memory mode " << getMemoryModeForParameter(opcode, 3) << " got a value of " << addrDest << " for destination address" << std::endl;
#endif

    product = val1*val2;
    res = m->put((long)addrDest, product);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << addrDest << std::endl;
        return res;
    }
    
    *new_ip = ip+IP_INCREMENT;
    
#ifdef DEBUG_OPERATIONS
    std::cerr << "   " << val1 << "*" << val2 << "=" << product << std::endl;
    std::cerr << "   next instruction pointer incremented by " << IP_INCREMENT << " to " << *new_ip << std::endl;
#endif

    return SUCCESS;
}
