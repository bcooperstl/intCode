#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
#include "program_manager.h"
#include "inputter_outputter.h"

#define FIRST_SIGNAL 0
#define MIN_PHASE 5
#define MAX_PHASE 9

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
    InputterOutputter eToA, aToB, bToC, cToD, dToE;
    Memory memA(*baseMem), memB(*baseMem), memC(*baseMem), memD(*baseMem), memE(*baseMem);
    ProgramRunner progA(&memA, "A"), progB(&memB, "B"), progC(&memC, "C"), progD(&memD, "D"), progE(&memE, "E");
    int rc;
    
    // link the inputs and outputs to the respective programs
    progA.setInputs(&eToA);
    progA.setOutputs(&aToB);
    progB.setInputs(&aToB);
    progB.setOutputs(&bToC);
    progC.setInputs(&bToC);
    progC.setOutputs(&cToD);
    progD.setInputs(&cToD);
    progD.setOutputs(&dToE);
    progE.setInputs(&dToE);
    progE.setOutputs(&eToA);

    // seed the inputs with phases and the initial signal to A
    eToA.add(a);
    aToB.add(b);
    bToC.add(c);
    cToD.add(d);
    dToE.add(e);
    
    eToA.add(FIRST_SIGNAL);

    // give the programs to the manager and let them run
    ProgramManager manager;
    manager.addRunner(&progA);
    manager.addRunner(&progB);
    manager.addRunner(&progC);
    manager.addRunner(&progD);
    manager.addRunner(&progE);
    
    rc=manager.runPrograms();
    if (rc != SUCCESS)
    {
        std::cerr << "Programs failed with error " << rc << std::endl;
        return rc;
    }
    
    rc = eToA.getNext(finalOutput);
    return rc;
}

int permute(Memory * baseMem, long * maxPower)
{
    *maxPower=0;
    int maxA, maxB, maxC, maxD, maxE;
    long power;
    int rc;
    
    for (int a=MIN_PHASE; a<=MAX_PHASE; a++)
    {
        for (int b=MIN_PHASE; b<=MAX_PHASE; b++)
        {
            for (int c=MIN_PHASE; c<=MAX_PHASE; c++)
            {
                for (int d=MIN_PHASE; d<=MAX_PHASE; d++)
                {
                    for (int e=MIN_PHASE; e<=MAX_PHASE; e++)
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
    long maxPower = 0;
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
    //rc = runPermutation(baseMem, 9, 8, 7, 6, 5, &maxPower);
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
