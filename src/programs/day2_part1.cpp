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
    
    // per instructions, set position 1 to 12 and position 2 to 2
    mem->put(1, 12);
    mem->put(2, 2);
    
    ProgramRunner * runner = new ProgramRunner(mem);
    rc = runner->run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    int pos0;
    mem->get(0, &pos0);
    std::cout << "********* Position 0 is " << pos0 << std::endl;
    
    delete runner;
    delete mem;
    
    return 0;
}
