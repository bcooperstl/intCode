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

int Multiplication::getIPIncrement()
{
    return IP_INCREMENT;
}

int Multiplication::performOperation(Memory * m, long ip)
{
    int addr1, addr2, val1, val2, addrDest, product, res;
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
    product = val1*val2;
    res = m->put((long)addrDest, product);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << addrDest << std::endl;
        return res;
    }
    std::cerr << "ip of " << ip << " resulted in parms of " << addr1 << ", " << addr2 << ", and " << addrDest << ".  ";
    std::cerr << val1 << "*" << val2 << "=" << product << std::endl;
    return SUCCESS;
}
