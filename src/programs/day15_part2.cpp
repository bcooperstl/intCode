#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "day15_runner.h"
#include "inputter_outputter.h"

int main (int argc, char * argv[])
{
    Area area;
    Point * startPoint = new Point(0,0, NULL);
    startPoint->setContents(WalkingArea);
    area.addPoint(startPoint);
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
    ProgramRunner intcode(baseMem, "Droid Mover");
    intcode.setService(true);
    Day15Runner myLogic("Day15Logic", &fromIntcode, &toIntcode, &area);
    
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
    
    std::cout << "Final map:" << std::endl;
    area.display(std::cout,0,0);
    
    area.pairPoints();
    area.setDistanceToOxygenSensor();
    
    int max=area.getMaximumDistanceToOxygen();
    
    std::cout << "*****Maximum distance from Oxygen Sensor is " << max << std::endl;
    
    delete baseMem;
    
    return 0;
}
