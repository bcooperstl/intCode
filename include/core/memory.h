#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <iostream>

#include "constants.h"

class Memory
{
private:
    int * m_ram; // Pointer to RAM. 
    long m_size;
    long m_max_used_address;
    int get(long address, int * result);
public:
    Memory(long size=MEM_SIZE);
    Memory(const Memory & other);
    ~Memory();
    int getImmediateMode(long address, int * result);
    int getPositionMode(long address, int * result);
    int get(long address, int mode, int * result);
    int put(long address, int value);
    long getSize();
    long getMaxUsedAddress();
    void reset();
    void dump(std::ostream & out);
};
    
#endif
