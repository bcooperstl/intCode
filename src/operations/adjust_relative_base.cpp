#include <cstring>
#include <iostream>

#include "adjust_relative_base.h"
#include "memory.h"

static std::string NAME="AdjustRelativeBase";
static int OPCODE=9;
static int IP_INCREMENT=2;

AdjustRelativeBase::AdjustRelativeBase() : Operation(NAME, OPCODE)
{
}

AdjustRelativeBase::~AdjustRelativeBase()
{
}

int AdjustRelativeBase::performOperation(Memory * m, long ip, int opcode, long * new_ip, InputterOutputter * inputs, InputterOutputter * outputs)
{
    long val, res;
    res = m->get(ip+1, getMemoryModeForParameter(opcode, 1), &val);
    if (res != SUCCESS)
    {
        std::cerr << "Error " << res << " received while retreving val from position " << ip+1 << std::endl;
        return res;
    }
    
    m->setRelativeBase(m->getRelativeBase()+val);
    
    *new_ip = ip+IP_INCREMENT;

#ifdef DEBUG_OPERATIONS
    std::cerr << "ip of " << ip << " resulted in relative base being adjusted by " << val << " to " << m->getRelativeBase() << std::endl;
    std::cerr << "  new ip incremented " << ip << " by " << IP_INCREMENT << " to " << *new_ip << std::endl;
#endif

    return SUCCESS;
}
