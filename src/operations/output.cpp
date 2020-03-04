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

int Output::getIPIncrement()
{
    return IP_INCREMENT;
}

int Output::performOperation(Memory * m, long ip)
{
    int val, res;
    res = m->get(ip+1, getMemoryModeForParameter(ip, 1), &val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val from position " << ip+1 << std::endl;
        return res;
    }
    
    std::cout << "***Output: " << val << std::endl;

    std::cerr << "ip of " << ip << " resulted in output value " << val << std::endl;
    return SUCCESS;
}
