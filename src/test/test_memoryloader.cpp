#include <iostream>
#include <cstring>

#include "memory_loader.h"
#include "memory.h"

void testString()
{
    std::cout << "Testing 256 byte memory from string with 1-10" << std::endl;
    std::string instr = "1,2,3,4,5,6,7,8,9,10";
    Memory * mem = new Memory(256);
    MemoryLoader::LoadFromString(mem, instr);
    mem->dump(std::cout);
    delete mem;
}

void testFile(std::string filename)
{
    std::cout << "Testing default sized memory from file " << filename << std::endl;
    Memory * mem = new Memory();
    MemoryLoader::LoadFromFile(mem, filename);
    mem->dump(std::cout);
    delete mem;
}

int main (int argc, char * argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return 1;
    }
    testString();
    testFile(std::string(argv[1]));
    return 0;
}
