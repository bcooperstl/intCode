#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "memory_loader.h"
#include "memory.h"
#include "constants.h"

int MemoryLoader::Load(Memory * m, std::istream * in)
{
    return 0;
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
