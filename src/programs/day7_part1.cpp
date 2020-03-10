#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"
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

int runAmplifier(Memory * baseMem, int phase, int signal, int *ampOutput)
{
    InputterOutputter in, out;
    in.add(phase);
    in.add(signal);
    
    int rc, res, val;
    
    Memory myMemory(*baseMem);
    ProgramRunner runner(&myMemory);
    runner.setInputs(&in);
    runner.setOutputs(&out);
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Program failed with error " << rc << std::endl;
        return rc;
    }
    
    rc = out.getNext(ampOutput);
    return rc;
}

int runPermutation(Memory * baseMem, int a, int b, int c, int d, int e, int * finalOutput)
{
    int rc, aRes, bRes, cRes, dRes, eRes;
    rc=runAmplifier(baseMem, a, FIRST_SIGNAL, &aRes);
    if (rc != SUCCESS)
        return rc;
    rc=runAmplifier(baseMem, b, aRes, &bRes);
    if (rc != SUCCESS)
        return rc;
    rc=runAmplifier(baseMem, c, bRes, &cRes);
    if (rc != SUCCESS)
        return rc;
    rc=runAmplifier(baseMem, d, cRes, &dRes);
    if (rc != SUCCESS)
        return rc;
    rc=runAmplifier(baseMem, e, dRes, &eRes);
    if (rc != SUCCESS)
        return rc;
    
    *finalOutput = eRes;
    return SUCCESS;
}

int permute(Memory * baseMem, int * maxPower)
{
    *maxPower=0;
    int maxA, maxB, maxC, maxD, maxE;
    int power, rc;
    
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
