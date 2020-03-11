#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "memory_loader.h"
#include "memory.h"
#include "constants.h"

int MemoryLoader::Load(Memory * m, std::istream * in)
{
    long counter=0;
    std::string line;
    if (m==NULL)
    {
        std::cerr << "null memory region given" << std::endl;
        return ERR_NULL;
    }
    if (!in->good())
    {
        std::cerr << "Error loading memory - bad stream" << std::endl;
        return ERR_NOFILE;
    }
    m->reset();
    while (std::getline(*in, line, INFILE_DELIM))
    {
        int value = atoi(line.c_str());
#ifdef DEBUG_MEMORY
        std::cerr << "Loading " << value << " from input [" << line << "] to position " << counter << std::endl;
#endif
        m->put(counter++, value);
    }
    return SUCCESS;
}

int MemoryLoader::LoadFromString(Memory * m, std::string input)
{
    std::istringstream instring(input);
    return Load(m, &instring);
}

int MemoryLoader::LoadFromFile(Memory * m, std::string filename)
{
    std::ifstream infile(filename);
    if(!infile.is_open())
    {
        std::cerr << "Error opening file " << filename << std::endl;
        return ERR_NOFILE;
    }
    int ret = Load(m, &infile);
    infile.close();
    return ret;
}
