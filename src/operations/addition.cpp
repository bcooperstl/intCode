#include <cstring>
#include <iostream>

#include "addition.h"
#include "memory.h"

static std::string NAME="Addition";
static int OPCODE=1;
static int IP_INCREMENT=4;

Addition::Addition() : Operation(NAME, OPCODE)
{
}

Addition::~Addition()
{
}

int Addition::performOperation(Memory * m, long ip, int opcode, long * new_ip)
{
    int val1, val2, addrDest, sum, res;
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
    sum = val1+val2;
    res = m->put((long)addrDest, sum);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << addrDest << std::endl;
        return res;
    }
    
    *new_ip = ip+IP_INCREMENT;
    
    std::cerr << "ip of " << ip << " resulted in parms of " << val1 << ", " << val2 << ", and " << addrDest << ".  ";
    std::cerr << val1 << "+" << val2 << "=" << sum << std::endl;
    std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;
    
    return SUCCESS;
}
