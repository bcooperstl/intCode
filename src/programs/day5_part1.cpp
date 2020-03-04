#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"

int main (int argc, char * argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return 1;
    }

    Memory * mem = new Memory();
    int rc = MemoryLoader::LoadFromFile(mem, argv[1]);
    if (rc)
    {
        std::cerr << "Error loading from file " << argv[1] << std::endl;
        delete mem;
        exit(1);
    }
    
    ProgramRunner * runner = new ProgramRunner(mem);
    rc = runner->run();
    if (rc != SUCCESS)
    {
        std::cerr << "Program failed with error " << rc << std::endl;
        exit(1);
    }
    
    delete runner;
    delete mem;
    
    std::cout << "***** See final output above for answer" << std::endl;
    
    return 0;
}
