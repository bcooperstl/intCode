#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "ascii_inputter_outputter.h"
#include "day25_part1_runner.h"

int main (int argc, char * argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return 1;
    }

    Memory * baseMem = new Memory();
    int rc = MemoryLoader::LoadFromFile(baseMem, argv[1]);
    if (rc)
    {
        std::cerr << "Error loading from file " << argv[1] << std::endl;
        delete baseMem;
        exit(1);
    }
    
    ProgramManager manager;
    AsciiInputterOutputter toIntcode, fromIntcode; // toIncode will be intcode's input and the day1runner's output. fromIntcode will be the opposite.
    ProgramRunner intcode(baseMem, "Intcode Droid");
    
    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);
    intcode.setService(true); // so it ends when the other program ends
    
    Day25Part1Runner myLogic("Interactive IO", &fromIntcode, &toIntcode);
    
    manager.addRunner(&myLogic);
    manager.addRunner(&intcode);
    
    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Program failed with error " << rc << std::endl;
        return rc;
    }
    
    delete baseMem;
        
    return 0;
}
