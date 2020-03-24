#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "inputter_outputter.h"

#define INPUT 1

int main (int argc, char * argv[])
{
    int maxPower = 0;
    long finalOutput;
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
    
    InputterOutputter inputter, outputter;
    ProgramRunner program(baseMem);

    
    // link the inputs and outputs to the respective programs
    program.setInputs(&inputter);
    program.setOutputs(&outputter);

    // set the one input value
    inputter.add(INPUT);

    // give the programs to the manager and let them run
    ProgramManager manager;
    manager.addRunner(&program);
    
    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    rc = outputter.getNext(&finalOutput);
    
    delete baseMem;
    
    if (rc == SUCCESS)
    {
        std::cout << "***** Final output value is " << finalOutput << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
