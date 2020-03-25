#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "day11_part1_runner.h"
#include "inputter_outputter.h"

#define START_SIZE 2
#define START_X 0
#define START_Y 0
#define START_DIRECTION north

int main (int argc, char * argv[])
{
    Side side(START_SIZE, START_X, START_Y, START_DIRECTION);
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
    
    InputterOutputter toIntcode, fromIntcode; // toIncode will be intcode's input and the day1runner's output. fromIntcode will be the opposite.
    ProgramRunner intcode(baseMem, "Intcode Robot");
    Day11Part1Runner myLogic("Day11Logic", &fromIntcode, &toIntcode, &side);
    
    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);


    // give the programs to the manager and let them run
    ProgramManager manager;
    manager.addRunner(&myLogic);
    manager.addRunner(&intcode);

    rc=manager.runPrograms();
    side.dump(std::cout);
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    delete baseMem;
    
    if (rc == SUCCESS)
    {
        std::cout << "***** Total number of painted panels is " << side.getPaintedCount() << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
