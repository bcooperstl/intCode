#include <cstring>
#include <iostream>

#include "equals.h"
#include "memory.h"

static std::string NAME="Equals";
static int OPCODE=8;
static int IP_INCREMENT=4;

Equals::Equals() : Operation(NAME, OPCODE)
{
}

Equals::~Equals()
{
}

int Equals::performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs)
{
    int val1, val2, destAddr, destVal, res;

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

    res = m->getImmediateMode(ip+3, &destAddr);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving destAddr from position " << ip+3 << std::endl;
        return res;
    }
    
    destVal = (val1 == val2) ? 1 : 0;
    
    res = m->put((long)destAddr, destVal);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << destAddr << std::endl;
        return res;
    }

    *new_ip = ip+IP_INCREMENT;

    std::cerr << "ip of " << ip << " resulted in parm of " << val1 << " & " << val2 << ". Stores result of " << val1 << "==" << val2 << "=" << destVal << " in " << destAddr << std::endl;
    std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;

    return SUCCESS;
}
