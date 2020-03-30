#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "day13_part1_runner.h"
#include "inputter_outputter.h"

int main (int argc, char * argv[])
{
    Screen screen;
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
    ProgramRunner intcode(baseMem, "Intcode BallGame");
    Day13Part1Runner myLogic("Day13Logic", &fromIntcode, &screen);
    
    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);


    // give the programs to the manager and let them run
    ProgramManager manager;
    manager.addRunner(&intcode);
    manager.addRunner(&myLogic);

    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    delete baseMem;
    
    int blockCount=0;
    Tile * tmp;
    for (int i=0; i<screen.getNumRows(); i++)
    {
        for (int j=0; j<screen.getNumCols(); j++)
        {
            screen.getTile(i,j,&tmp);
            if (tmp->getValue()=='x')
                blockCount++;
        }
    }
    
    if (rc == SUCCESS)
    {
        std::cout << "***** Final screen is: " << std::endl;
        screen.display(std::cout);
        std::cout << "***** Final block count is " << blockCount << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
