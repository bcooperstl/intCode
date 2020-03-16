#include <cstring>
#include <iostream>

#include "jump_if_true.h"
#include "memory.h"

static std::string NAME="JumpIfTrue";
static int OPCODE=5;
static int IP_INCREMENT=3;

JumpIfTrue::JumpIfTrue() : Operation(NAME, OPCODE)
{
}

JumpIfTrue::~JumpIfTrue()
{
}

int JumpIfTrue::performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs)
{
    long compare_val, new_ip_val, res;
    res = m->get(ip+1, getMemoryModeForParameter(opcode, 1), &compare_val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addr from position " << ip+1 << std::endl;
        return res;
    }

    res = m->get(ip+2, getMemoryModeForParameter(opcode, 2), &new_ip_val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving addr from position " << ip+1 << std::endl;
        return res;
    }

    if (compare_val != 0)
    {
        *new_ip=new_ip_val;
#ifdef DEBUG_OPERATIONS
        std::cerr << "ip of " << ip << " resulted in non-zero value of " << compare_val << ", and new ip of " << new_ip_val << ".  ";
        std::cerr << "  new ip set to " << *new_ip << std::endl;
#endif
    }
    else
    {
        *new_ip = ip+IP_INCREMENT;
#ifdef DEBUG_OPERATIONS
        std::cerr << "ip of " << ip << " resulted in zero value of " << compare_val << ".  ";
        std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;
#endif
    }

    return SUCCESS;
}
