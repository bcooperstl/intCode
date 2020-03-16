#include <cstring>
#include <iostream>
#include <map>

#include "memory.h"
#include "memory_page.h"
#include "constants.h"

Memory::Memory(long page_size)
{
    m_page_size = page_size;
}

Memory::Memory(const Memory & other)
{
    m_page_size = other.m_page_size;
    for (std::map<long, MemoryPage *>::const_iterator iter=other.m_pages.begin(); iter!=other.m_pages.end(); ++iter)
    {
        m_pages.insert(std::pair<long, MemoryPage *>(iter->first, new MemoryPage(*iter->second)));
    }
}

Memory::~Memory()
{
    for (std::map<long, MemoryPage *>::iterator iter=m_pages.begin(); iter!=m_pages.end(); ++iter)
    {
        delete iter->second;
    }
    m_pages.clear();
}

MemoryPage * Memory::createBlankPage()
{
    MemoryPage * page = new MemoryPage();
    return page;
}

int Memory::storePage(long pageNumber, MemoryPage * page)
{
    std::map<long, MemoryPage *>::iterator mapPage = m_pages.find(pageNumber);
    if (mapPage != m_pages.end())
    {
        std::cerr << "Attempting to store duplicate page " << pageNumber << std::endl;
        return ERR_DUP_PAGE;
    }
    m_pages.insert(std::pair<long, MemoryPage *>(pageNumber, page));
    return SUCCESS;
}

int Memory::getPage(long pageNumber, MemoryPage ** page)
{
    std::map<long, MemoryPage *>::iterator mapPage = m_pages.find(pageNumber);
    if (mapPage == m_pages.end())
    {
        std::cerr << "No page " << pageNumber << " found." << std::endl;
        return ERR_NO_PAGE;
    }
    *page = mapPage->second;
    return SUCCESS;
}

void Memory::calculatePageNumberOffset(long address, long & pageNumber, int & offset)
{
    pageNumber = address / m_page_size;
    offset = address % m_page_size;
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::get(long address, long * result)
{
    long pageNumber;
    int offset;
    MemoryPage * page = NULL;
    if (address < 0)
        return ERR_ADDRESS;
    calculatePageNumberOffset(address, pageNumber, offset);

    int rc = getPage(pageNumber, &page);
    if (rc != SUCCESS)
        return rc;
    return page->get(offset, result);
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::getImmediateMode(long address, long * result)
{
    return get(address, result);
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::getPositionMode(long address, long * result)
{
    int res;
    long position;
    if (address < 0)
        return ERR_ADDRESS;
    // first get the position stored in memory at address
    res = get(address, &position);
    if (res != SUCCESS)
        return res;
    
    // now check to ensrue position is in ram
    if (position < 0)
        return ERR_ADDRESS;
    
    // return the value at position
    return get(position, result);
}

// get will return SUCCESS on success.
// get will return ERR_ADDRESS on invalid address
int Memory::get(long address, int mode, long * result)
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
int Memory::put(long address, long value)
{
#ifdef DEBUG_MEMORY
    std::cerr << "Putting " << value << " at " << address << std::endl;
#endif
    long pageNumber;
    int offset;
    MemoryPage * page = NULL;
    if (address < 0)
        return ERR_ADDRESS;

    calculatePageNumberOffset(address, pageNumber, offset);
#ifdef DEBUG_MEMORY
    std::cerr << "address " << address << " is pageNumber " << pageNumber << " offset " << offset << std::endl;
#endif
    int rc = getPage(pageNumber, &page);
    
    if (rc != SUCCESS)
    {
#ifdef DEBUG_MEMORY
        std::cerr << "Creating memory page " << pageNumber << std::endl;
#endif
        page = createBlankPage();
        rc = storePage(pageNumber, page);
        if (rc != SUCCESS)
            return rc;
    }
    
    return page->put(offset, value);
}

int Memory::getPageSize()
{
    return m_page_size;
}

void Memory::reset()
{
    for (std::map<long, MemoryPage *>::iterator iter=m_pages.begin(); iter!=m_pages.end(); ++iter)
    {
        delete iter->second;
    }
    m_pages.clear();
}

void Memory::dump(std::ostream & out)
{
    out << "Dumping all of memory" << std::endl;
    for (std::map<long, MemoryPage *>::iterator iter=m_pages.begin(); iter!=m_pages.end(); ++iter)
    {
        iter->second->dumpPage(out, iter->first);
    }
}
