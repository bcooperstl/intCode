#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"

#define TARGET 19690720

int main (int argc, char * argv[])
{
    int foundNoun, foundVerb;
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return 1;
    }

    Memory * memFile = new Memory();
    int rc = MemoryLoader::LoadFromFile(memFile, argv[1]);
    if (rc)
    {
        std::cerr << "Error loading from file " << argv[1] << std::endl;
        delete memFile;
        exit(1);
    }
    
    bool found = false;
    for (int noun=0; noun<100 && !found; noun++)
    {
        for (int verb=0; verb<100 && !found; verb++)
        {
            Memory * memCurr= new Memory(*memFile);
            memCurr->put(1, noun);
            memCurr->put(2, verb);
    
            ProgramRunner * runner = new ProgramRunner(memCurr);
            rc = runner->run();
            if (rc != SUCCESS)
            {
                std::cerr << "Test failed with error " << rc << std::endl;
                exit(1);
            }
    
            long pos0;
            memCurr->getImmediateMode(0, &pos0);
            
            if (pos0==TARGET)
            {
                found=true;
                foundNoun = noun;
                foundVerb = verb;
            }
            
            delete runner;
            delete memCurr;
        }
    }
    delete memFile;
    
    if (found)
    {
        std::cout << "***** Target " << TARGET << " found with noun = " << foundNoun << " verb = " << foundVerb << " calculated value = " << 100 * foundNoun + foundVerb << std::endl;
    }
    else
    {
        std::cout << "No matching set of noun and verb with result in target " << TARGET << std::endl;
    }
    
    return 0;
}
