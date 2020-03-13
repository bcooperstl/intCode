#include <cstring>
#include <iostream>

#include "memory_page.h"
#include "constants.h"

MemoryPage::MemoryPage(long size)
{
    m_size = size;
    m_ram = new long[m_size];
    m_min_used_offset = m_size;
    m_max_used_offset = 0;
    bzero(m_ram, sizeof(long)*m_size);
}

MemoryPage::MemoryPage(const MemoryPage & other)
{
    m_size = other.m_size;
    m_ram = new long[m_size];
    memcpy(m_ram, other.m_ram, sizeof(long)*m_size);
    m_min_used_offset=other.m_min_used_offset;
    m_max_used_offset=other.m_max_used_offset;
}

MemoryPage::~MemoryPage()
{
    if (m_ram != NULL)
    {
        delete m_ram;
    }
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int MemoryPage::get(int offset, long * result)
{
    if (offset < 0 || offset > m_size)
        return ERR_ADDRESS;
    *result = m_ram[offset];
    return SUCCESS;
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int MemoryPage::put(int offset, long value)
{
    if (offset < 0 || offset > m_size)
        return ERR_ADDRESS;
    m_ram[offset] = value;
    if (offset > m_max_used_offset)
        m_max_used_offset = offset;
    if (offset < m_min_used_offset)
        m_min_used_offset = offset;
    return SUCCESS;
}

int MemoryPage::getSize()
{
    return m_size;
}

int MemoryPage::getMaxUsedOffset()
{
    return m_max_used_offset;
}

int MemoryPage::getMinUsedOffset()
{
    return m_min_used_offset;
}

void MemoryPage::reset()
{
    if (m_ram != NULL)
    {
        delete m_ram;
    }
    m_ram = new long[m_size];
    m_max_used_offset = 0;
    m_min_used_offset = m_size;
    bzero(m_ram, sizeof(long)*m_size);    
}

void MemoryPage::dumpPage(std::ostream & out, int base)
{
    out << "MemoryPage usage: min_offset " << m_min_used_offset << " to max offset " << m_max_used_offset << std::endl;
    bool first = true;
    for (int i=m_min_used_offset; i<=m_max_used_offset; i++)
    {
        if (i%16 == 0 || first)
        {
            if (!first)
            {
                out << std::endl;
            }
            out << base*m_size+i << '-' << base*m_size+((i/16+1)*16-1);
        }
        out << "  " << m_ram[i];
    }
    out << std::endl;
}
