#include <cstring>
#include <iostream>

#include "input.h"
#include "memory.h"

static std::string NAME="Input";
static int OPCODE=3;
static int IP_INCREMENT=2;

Input::Input() : Operation(NAME, OPCODE)
{
}

Input::~Input()
{
}

int Input::performOperation(Memory * m, long ip, int opcode, long * new_ip)
{
    int addr, val, res;
    res = m->getImmediateMode(ip+1, &addr);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addr from position " << ip+1 << std::endl;
        return res;
    }

    std::cout << "***Enter an integer >";
    std::cin >> val;
    
    res = m->put((long)addr, val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while storing result into position " << addr << std::endl;
        return res;
    }

    *new_ip = ip+IP_INCREMENT;

    std::cerr << "ip of " << ip << " resulted in parm of " << addr << ". Stored input value " << val << std::endl;
    std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;

    return SUCCESS;
}
