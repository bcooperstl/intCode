#include <iostream>
#include <cstring>
#include <string>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "day17_part2_runner.h"
#include "inputter_outputter.h"

void addStringToInputs(InputterOutputter * inputter, std::string values)
{
    for (int i=0; i<values.length(); i++)
    {
        inputter->add((long)values[i]);
    }
}

int main (int argc, char * argv[])
{
    Screen screen;
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return 1;
    }
    
    std::string mainProgram("A,B,A,C,B,A,C,A,C,B\n");
    std::string programA("L,12,L,8,L,8\n");
    std::string programB("L,12,R,4,L,12,R,6\n");
    std::string programC("R,4,L,12,L,12,R,6\n");
    std::string enableVideo("y\n");

    Memory * baseMem = new Memory();
    int rc = MemoryLoader::LoadFromFile(baseMem, argv[1]);
    if (rc)
    {
        std::cerr << "Error loading from file " << argv[1] << std::endl;
        delete baseMem;
        exit(1);
    }
    
    baseMem->put(0,2); // hardcode position 0 to 2 to make the robot move
    
    InputterOutputter toIntcode, fromIntcode; // toIncode will be intcode's input and the day1runner's output. fromIntcode will be the opposite.
    ProgramRunner intcode(baseMem, "Intcode Scaffold Robot");
    Day17Part2Runner myLogic("Day17Logic", &fromIntcode, &screen);
    
    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);
    
    // Add the data to the inputs.
    addStringToInputs(&toIntcode, mainProgram);
    addStringToInputs(&toIntcode, programA);
    addStringToInputs(&toIntcode, programB);
    addStringToInputs(&toIntcode, programC);
    addStringToInputs(&toIntcode, enableVideo);
    
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
    
    int sum=0;
    int rows=myLogic.getRow();
    int cols=myLogic.getCol();
    Tile *current, *up, *down, *left, *right;
        
    if (rc == SUCCESS)
    {
        std::cout << "***** Final screen is: " << std::endl;
        screen.display(std::cout);
        std::cout << "***** Final dust value is " << myLogic.getFinalValue() << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
