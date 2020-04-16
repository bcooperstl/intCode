#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "day17_runner.h"
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
    ProgramRunner intcode(baseMem, "Intcode Scaffold Robot");
    Day17Runner myLogic("Day17Logic", &fromIntcode, &screen);
    std::cerr << "screen rows is " << screen.getNumRows() << std::endl;
    std::cerr << "rows is " << myLogic.getRow() << std::endl;
    
    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);


    // give the programs to the manager and let them run
    ProgramManager manager;
    manager.addRunner(&intcode);
    manager.addRunner(&myLogic);
    std::cerr << "rows is " << myLogic.getRow() << std::endl;

    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    delete baseMem;
    
    int sum=0;
    int rows=myLogic.getRow();
    int cols=myLogic.getCol();
    Tile *current, *up, *down, *left, *right;
    
    std::cerr << "There are " << rows << " rows and " << cols << " columns" << std::endl;
    
    for (int i=1; i<rows-1; i++)
    {
        for (int j=1; j<cols-1; j++)
        {
            screen.getTile(i,j,&current);
            if (current->getValue()=='#')
            {
                screen.getTile(i-1,j,&up);
                screen.getTile(i+1,j,&down);
                screen.getTile(i,j-1,&left);
                screen.getTile(i,j+1,&right);
                if (up->getValue()=='#' && down->getValue()=='#' && left->getValue()=='#' && right->getValue()=='#')
                {
                    int score=i*j;
                    std::cerr << "Intersection at row=" << i << " column=" << j << " for score=" << score << std::endl;
                    sum+=score;
                }
            }
        }
    }
    
    if (rc == SUCCESS)
    {
        std::cout << "***** Final screen is: " << std::endl;
        screen.display(std::cout);
        std::cout << "***** Sum of intersection is " << sum << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
