#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "day23_part2_runner.h"
#include "inputter_outputter.h"

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
    Day23Part2Runner networkSwitch("Day23 Switch");
    
    manager.addRunner(&networkSwitch); // run this first so there is a -1 waiting on every input
    
    InputterOutputter toNics[NUM_NICS], fromNics[NUM_NICS]; // toNics goes to the Intcode NIC program, fromNics is output from the Intcode NIC program
    ProgramRunner * nics[NUM_NICS];
    Memory * mem[NUM_NICS];
    for (int i=0; i<NUM_NICS; i++)
    {
        // dupe the base memory for this instance
        mem[i]=new Memory(*baseMem);
        
        std::string name="Intcode NIC "+std::to_string(i); // make the name
        
        // send the id as an input to the nic
        toNics[i].add(i);
        
        // create the program runner for this NIC and assign the inputs and outputs
        nics[i] = new ProgramRunner(mem[i], name);
        nics[i]->setInputs(&toNics[i]);
        nics[i]->setOutputs(&fromNics[i]);
        nics[i]->setService(true); // set these as services so that when the switch is done, they all shut down cleanly.
                
        // hook in the inputs and outputs to the switch
        networkSwitch.addNic(i, &toNics[i], &fromNics[i]);
        
        // hook this nic into the manager
        manager.addRunner(nics[i]);
    }
    
    // let the manager do its thing
    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    // clean some stuff up
    for (int i=0; i<NUM_NICS; i++)
    {
        delete nics[i];
        delete mem[i];
    }
    
    delete baseMem;
    
    if (rc == SUCCESS)
    {
        std::cout << "***** The first duplicate y value for the NAT is " << networkSwitch.getFirstDupeNatY() << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
