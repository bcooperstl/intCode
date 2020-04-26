#include <iostream>
#include <cstring>
#include <cstdlib>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "inputter_outputter.h"

#define TARGET_DIMENSION 100
#define START_ROW 8

#define STATIONARY '.'
#define PULLED '#'

bool isPulled(int x, int y, Memory * baseMem)
{
    InputterOutputter toIntcode, fromIntcode; // toIncode will be intcode's input. fromIntcode will be its outputs.
    
    long outVal;
    Memory * memCpy = new Memory(*baseMem);
    ProgramRunner intcode(memCpy, "Intcode Drone System");

    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);

    toIntcode.add(x);
    toIntcode.add(y);
    int rc=intcode.run();
    if (rc != SUCCESS && rc != INPUT_WAIT)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        delete memCpy;
        exit(rc);
    }
    
    rc=fromIntcode.getNext(&outVal);
    if (rc != SUCCESS)
    {
        std::cerr << "Error fetching output with error " << rc << std::endl;
        delete memCpy;
        exit(rc);
    }
    delete memCpy;
    return (outVal==1);
}

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
    
    int prior_start_col=0;
    int prior_start_row=START_ROW-1;
    int found_start_col;
    int found_start_row;
    bool found=false;
    while (!found)
    {
        int curr_row=prior_start_row+1;
        int curr_col=prior_start_col;
        // first find the first column in this row that is pulled
        while (!isPulled(curr_col, curr_row, baseMem))
        {
            curr_col++;
        }
        std::cout << "For row " << curr_row << " the first pulled column is " << curr_col << std::endl;
        prior_start_col=curr_col;
        if (!isPulled(curr_col+TARGET_DIMENSION-1, curr_row, baseMem))
        {
            std::cout << "Row " << curr_row << " does not have a wide enough beam. Going to next row" << std::endl;
            prior_start_row=curr_row;
            continue;
        }
        while (isPulled(curr_col, curr_row, baseMem) && isPulled(curr_col+TARGET_DIMENSION-1, curr_row, baseMem))
        {
            if (isPulled(curr_col, curr_row+TARGET_DIMENSION-1, baseMem) && isPulled(curr_col+TARGET_DIMENSION-1, curr_row+TARGET_DIMENSION-1, baseMem))
            {
                std::cout << "Range fround from cols " << curr_col << "-" << curr_col+TARGET_DIMENSION-1 << " and rows " << curr_row << "-" << curr_row+TARGET_DIMENSION-1 << std::endl;                
                found=true;
                found_start_col=curr_col;
                found_start_row=curr_row;
                break;
            }
            else
            {
                curr_col++;
            }
        }
        prior_start_row=curr_row;
    }
    
    delete baseMem;
    int final_value=10000*found_start_col+found_start_row;
    std::cout << "***** Final value is " << final_value << std::endl;

    return 0;
}
