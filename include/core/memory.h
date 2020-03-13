#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <iostream>
#include <map>

#include "constants.h"
#include "memory_page.h"

class Memory
{
private:
    int m_page_size;
    std::map<long, MemoryPage *> m_pages; // Map of memory pages.  
    int get(long address, long * result);
    void calculatePageNumberOffset(long address, long & pageNumber, int & offset);
    int getPage(long pageNumber, MemoryPage * page);
    MemoryPage * createBlankPage();
    int storePage(long pageNumber, MemoryPage * page);
public:
    Memory(long page_size=MEM_PAGE_SIZE);
    Memory(const Memory & other);
    ~Memory();
    int getImmediateMode(long address, long * result);
    int getPositionMode(long address, long * result);
    int get(long address, int mode, long * result);
    int put(long address, long value);
    int getPageSize();
    void reset();
    void dump(std::ostream & out);
};
    
#endif
