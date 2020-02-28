#include <cstring>
#include <iostream>

#include "addition.h"
#include "memory.h"

static std::string NAME="Addition";
static int OPCODE=1;

Addition::Addition() : Operation(NAME, OPCODE)
{
}

Addition::~Addition()
{
}

int Addition::performOperation(Memory * m, long ip)
{
    int addr1, addr2, val1, val2, addrDest, sum, res;
    res = m->get(ip+1, &addr1);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addr1 from position " << ip+1 << std::endl;
        return res;
    }
    res = m->get(ip+2, &addr2);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addr2 from position " << ip+2 << std::endl;
        return res;
    }
    res = m->get(ip+3, &addrDest);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addrDest from position " << ip+3 << std::endl;
        return res;
    }
    res = m->get((long)addr1, &val1);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val1 from position " << addr1 << std::endl;
        return res;
    }
    res = m->get((long)addr2, &val2);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val2 from position " << addr2 << std::endl;
        return res;
    }
    sum = val1+val2;
    res = m->put((long)addrDest, sum);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << addrDest << std::endl;
        return res;
    }
    std::cerr << "ip of " << ip << " resulted in parms of " << addr1 << ", " << addr2 << ", and " << addrDest << ".  ";
    std::cerr << val1 << "+" << val2 << "=" << sum << std::endl;
    return SUCCESS;
}
