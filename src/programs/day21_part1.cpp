#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "ascii_inputter_outputter.h"

#define NUM_INSTRUCTIONS 15

int main (int argc, char * argv[])
{
    std::string springscript[NUM_INSTRUCTIONS]=
    {
        "OR D J",
        "OR A T",
        "AND B T",
        "AND C T",
        "NOT T T",
        "AND T J",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };
    
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
    
    AsciiInputterOutputter toIntcode, fromIntcode; // toIncode will be intcode's input and the day1runner's output. fromIntcode will be the opposite.
    ProgramRunner intcode(baseMem, "Intcode Droid Robot");
    
    intcode.setInputs(&toIntcode);
    intcode.setOutputs(&fromIntcode);

    // load the input
    for (int i=0; i<NUM_INSTRUCTIONS; i++)
    {
        if (springscript[i].length() >=1 )
        {
            toIntcode.add(springscript[i]);
            toIntcode.addNewline();
        }
    }
    
    toIntcode.add(std::string("WALK"));
    toIntcode.addNewline();

    rc=intcode.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Program failed with error " << rc << std::endl;
        return rc;
    }
    
    delete baseMem;
    
    if (fromIntcode.hasAvailableAscii())
    {
        std::string asciiOut;
        rc = fromIntcode.getNextString(asciiOut);
        if (rc != SUCCESS)
        {
            std::cerr << "Error getting ASCII output" << std::endl;
            return rc;
        }
        std::cout << "Final display: " << std::endl << asciiOut << std::endl;
    }
    long damage;
    rc = fromIntcode.getNext(&damage);
    if (rc == SUCCESS)
    {
        std::cout << "***** Final damage is: " << damage << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;    
    }
    
    return 0;
}
