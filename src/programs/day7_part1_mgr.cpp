#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "inputter_outputter.h"

#define FIRST_SIGNAL 0

bool isValid(int a, int b, int c, int d, int e)
{
    if (a==b)
        return false;
    if (a==c)
        return false;
    if (a==d)
        return false;
    if (a==e)
        return false;
    if (b==c)
        return false;
    if (b==d)
        return false;
    if (b==e)
        return false;
    if (c==d)
        return false;
    if (c==e)
        return false;
    if (d==e)
        return false;
    return true;
}

int runPermutation(Memory * baseMem, int a, int b, int c, int d, int e, long * finalOutput)
{
    InputterOutputter inA, aToB, bToC, cToD, dToE, outE;
    Memory memA(*baseMem), memB(*baseMem), memC(*baseMem), memD(*baseMem), memE(*baseMem);
    ProgramRunner progA(&memA, "A"), progB(&memB, "B"), progC(&memC, "C"), progD(&memD, "D"), progE(&memE, "E");
    int rc;
    
    // link the inputs and outputs to the respective programs
    progA.setInputs(&inA);
    progA.setOutputs(&aToB);
    progB.setInputs(&aToB);
    progB.setOutputs(&bToC);
    progC.setInputs(&bToC);
    progC.setOutputs(&cToD);
    progD.setInputs(&cToD);
    progD.setOutputs(&dToE);
    progE.setInputs(&dToE);
    progE.setOutputs(&outE);

    // seed the inputs with phases and the initial signal to A
    inA.add(a);
    aToB.add(b);
    bToC.add(c);
    cToD.add(d);
    dToE.add(e);
    
    inA.add(FIRST_SIGNAL);

    // give the programs to the manager and let them run
    ProgramManager manager;
    manager.addProgramRunner(&progA);
    manager.addProgramRunner(&progB);
    manager.addProgramRunner(&progC);
    manager.addProgramRunner(&progD);
    manager.addProgramRunner(&progE);
    
    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    rc = outE.getNext(finalOutput);
    return rc;
}

int permute(Memory * baseMem, int * maxPower)
{
    *maxPower=0;
    int maxA, maxB, maxC, maxD, maxE;
    long power;
    int rc;
    
    for (int a=0; a<=4; a++)
    {
        for (int b=0; b<=4; b++)
        {
            for (int c=0; c<=4; c++)
            {
                for (int d=0; d<=4; d++)
                {
                    for (int e=0; e<=4; e++)
                    {
                        if (isValid(a, b, c, d, e))
                        {
                            rc=runPermutation(baseMem, a, b, c, d, e, &power);
                            if (rc != SUCCESS)
                            {
                                return rc;
                            }
                            if (power > *maxPower)
                            {
                                *maxPower = power;
                                maxA=a;
                                maxB=b;
                                maxC=c;
                                maxD=d;
                                maxE=e;
                            }
                        }
                    }
                }
            }
        }
    }
    
    std::cout << "Maximum power " << *maxPower << " found for a=" << maxA << ", b=" << maxB << ", c=" << maxC << ", d=" << maxD << ", e=" << maxE << std::endl;
    
    return SUCCESS;
}

int main (int argc, char * argv[])
{
    int maxPower = 0;
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
    
    rc = permute(baseMem, &maxPower);
    //rc = runPermutation(baseMem, 0, 1, 2, 3, 4, &maxPower);
    delete baseMem;
    
    if (rc == SUCCESS)
    {
        std::cout << "***** Maximum power is " << maxPower << std::endl;
    }
    else
    {
        std::cerr << "*****Errors occurred" << std::endl;
    }
    return 0;
}
