#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "screen.h"
#include "inputter_outputter.h"

#define MAX_X 50
#define MAX_Y 50

#define STATIONARY '.'
#define PULLED '#'

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
    InputterOutputter toIntcode, fromIntcode; // toIncode will be intcode's input. fromIntcode will be its outputs.
    
    long outVal;
    
    for (int x=0; x<MAX_X; x++)
    {
        for (int y=0; y<MAX_Y; y++)
        {
            Memory * memCpy = new Memory(*baseMem);
            ProgramRunner intcode(memCpy, "Intcode Drone System");
    
            intcode.setInputs(&toIntcode);
            intcode.setOutputs(&fromIntcode);

            toIntcode.add(x);
            toIntcode.add(y);
            rc=intcode.run();
            if (rc != SUCCESS && rc != INPUT_WAIT)
            {
                std::cerr << "Programs failed with error " << rc << std::endl;
                delete memCpy;
                return rc;
            }
            
            rc=fromIntcode.getNext(&outVal);
            if (rc != SUCCESS)
            {
                std::cerr << "Error fetching output with error " << rc << std::endl;
                delete memCpy;
                return rc;
            }
            screen.set(y,x,Tile(outVal==0?STATIONARY:PULLED));
            delete memCpy;
        }
    }
    
    delete baseMem;
    
    int pulledCount=0;
    Tile * tmp;
    for (int i=0; i<screen.getNumRows(); i++)
    {
        for (int j=0; j<screen.getNumCols(); j++)
        {
            screen.getTile(i,j,&tmp);
            if (tmp->getValue()==PULLED)
                pulledCount++;
        }
    }
    
    std::cout << "***** Final screen is: " << std::endl;
    screen.display(std::cout);
    std::cout << "***** Final pulled count is " << pulledCount << std::endl;

    return 0;
}
