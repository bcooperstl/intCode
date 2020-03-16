#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"


std::string test1 = "1002,4,3,4,33";
std::string res1 = "1002,4,3,4,99";
std::string test2 = "1101,100,-1,4,0";
std::string res2 = "1101,100,-1,4,99";

void runTest(std::string test, std::string res)
{
    Memory testMem(256);
    Memory resMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    MemoryLoader::LoadFromString(&resMem, res);
    testMem.dump(std::cout);
    
    ProgramRunner runner(&testMem);
    int rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
//    if (testMem.getMaxUsedAddress() != resMem.getMaxUsedAddress())
//    {
//        std::cerr << "Test failed - max used address was " << testMem.getMaxUsedAddress() << "  expected " << resMem.getMaxUsedAddress() << std::endl;
//        exit(1);
//    }
    
    long testVal, resVal, i;
    for (i=0; i<testMem.getPageSize(); i++)
    {
        testMem.getImmediateMode(i, &testVal);
        resMem.getImmediateMode(i, &resVal);
        if (testVal != resVal)
        {
            std::cerr << "Test failed - mismatch at " << i << "  expected " << resVal << " got " << testVal << std::endl;
            exit(1);
        }
    }
    std::cout << "Test passed - all " << i << " values matched" << std::endl;
}

int main (int argc, char * argv[])
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    std::cout << "Running test 1" << std::endl;
    runTest(test1, res1);
    std::cout << "Running test 2" << std::endl;
    runTest(test2, res2);

    return 0;
}
