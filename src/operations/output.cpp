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
    int val, res;
    res = m->get(ip+1, getMemoryModeForParameter(opcode, 1), &val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val from position " << ip+1 << std::endl;
        return res;
    }
    
    std::cout << "***Output: " << val << std::endl;
    if (outputs != NULL)
    {
        outputs->add(val);
    }

    *new_ip = ip+IP_INCREMENT;

    std::cerr << "ip of " << ip << " resulted in output value " << val << std::endl;
    std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;

    return SUCCESS;
}
