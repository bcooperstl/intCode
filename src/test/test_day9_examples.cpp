#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"


std::string output_self = "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99";
std::string large_output = "1102,34915192,34915192,7,4,7,99,0";
long large_output_result = 1219070632396864l;
std::string large_output_2 = "104,1125899906842624,99";
long large_output_2_result = 1125899906842624l;

void runTest_largeOutput(std::string test, long expectedResult)
{
    int rc;
    Memory testMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    testMem.dump(std::cout);
    InputterOutputter outputter;
    
    ProgramRunner runner(&testMem);
    runner.setOutputs(&outputter);
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    long actualResult;
    outputter.getNext(&actualResult);
    
    if (actualResult == expectedResult)
    {
        std::cout << "Results match - " << actualResult << "=" << expectedResult << std::endl;
    }
    else
    {
        std::cout << "***Results mismatch - received " << actualResult << " expected " << expectedResult << std::endl;
    }
}

void runTest_self(std::string test)
{
    int rc;
    Memory testMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    testMem.dump(std::cout);
    
    ProgramRunner runner(&testMem);
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare above outputs with expected: " << test << std::endl;
}

int main (int argc, char * argv[])
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    runTest_largeOutput(large_output, large_output_result);
    runTest_largeOutput(large_output_2, large_output_2_result);
    runTest_self(output_self);
    
    return 0;
}
