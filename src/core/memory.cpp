#include <cstring>

#include "memory.h"
#include "constants.h"

Memory::Memory(long size=MEM_SIZE)
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
