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
    int val1, val2, addrDest, product, res;
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
    res = m->getImmediateMode(ip+3, &addrDest);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addrDest from position " << ip+3 << std::endl;
        return res;
    }
    product = val1*val2;
    res = m->put((long)addrDest, product);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << addrDest << std::endl;
        return res;
    }
    
    *new_ip = ip+IP_INCREMENT;
    
#ifdef DEBUG_OPERATIONS
    std::cerr << "ip of " << ip << " resulted in parms of " << val1 << ", " << val2 << ", and " << addrDest << ".  ";
    std::cerr << val1 << "*" << val2 << "=" << product << std::endl;
    std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;
#endif

    return SUCCESS;
}
