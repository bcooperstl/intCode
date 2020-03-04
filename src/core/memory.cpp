#include <cstring>
#include <iostream>

#include "memory.h"
#include "constants.h"

Memory::Memory(long size)
{
    m_size = size;
    m_ram = new int[m_size];
    m_max_used_address = 0;
    bzero(m_ram, sizeof(int)*m_size);
}

Memory::Memory(const Memory & other)
{
    m_size = other.m_size;
    m_ram = new int[m_size];
    memcpy(m_ram, other.m_ram, sizeof(int)*m_size);
    m_max_used_address=other.m_max_used_address;
}

Memory::~Memory()
{
    if (m_ram != NULL)
    {
        delete m_ram;
    }
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::get(long address, int * result)
{
    if (address < 0 || address > m_size)
        return ERR_ADDRESS;
    *result = m_ram[address];
    return SUCCESS;
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::getImmediateMode(long address, int * result)
{
    return get(address, result);
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::getPositionMode(long address, int * result)
{
    int res, position;
    if (address < 0 || address > m_size)
        return ERR_ADDRESS;
    // first get the position stored in memory at address
    res = get(address, &position);
    if (res != SUCCESS)
        return res;
    
    // now check to ensrue position is in ram
    if (position < 0 || position > m_size)
        return ERR_ADDRESS;
    
    // return the value at position
    return get(position, result);
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::get(long address, int mode, int * result)
{
    switch (mode)
    {
        case MEM_MODE_POSITION:
            return getPositionMode(address, result);
        case MEM_MODE_IMMEDIATE:
            return getImmediateMode(address, result);
        default:
            std::cerr << "Invalid memory mode " << mode << std::endl;
            return ERR_INVALID_MEM_MODE;
    }
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::put(long address, int value)
{
    if (address < 0 || address > m_size)
        return ERR_ADDRESS;
    m_ram[address] = value;
    if (address > m_max_used_address)
        m_max_used_address = address;
    return SUCCESS;
}

long Memory::getSize()
{
    return m_size;
}

long Memory::getMaxUsedAddress()
{
    return m_max_used_address;
}

void Memory::reset()
{
    if (m_ram != NULL)
    {
        delete m_ram;
    }
    m_ram = new int[m_size];
    m_max_used_address = 0;
    bzero(m_ram, sizeof(int)*m_size);    
}

void Memory::dump(std::ostream & out)
{
    out << "Memory usage: max address " << m_max_used_address << " of size " << m_size << "(0-" << m_size-1 << ")" << std::endl;
    for (int i=0; i<=m_max_used_address; i++)
    {
        if (i%16 == 0)
        {
            if (i != 0)
            {
                out << std::endl;
            }
            out << i << '-' << i+15;
        }
        out << "  " << m_ram[i];
    }
    out << std::endl;
}
