#ifndef __MEMORY_PAGE_H__
#define __MEMORY_PAGE_H__

#include <iostream>

#include "constants.h"

class MemoryPage
{
private:
    int m_size;
    long * m_ram; // Pointer to RAM. 
    int m_min_used_offset;
    int m_max_used_offset;
public:
    MemoryPage(long size=MEM_PAGE_SIZE);
    MemoryPage(const MemoryPage & other);
    ~MemoryPage();
    int get(int offset, long * result);
    int put(int offset, long value);
    int getSize();
    int getMinUsedOffset();
    int getMaxUsedOffset();
    void reset();
    void dumpPage(std::ostream & out, int base);
};
    
#endif
