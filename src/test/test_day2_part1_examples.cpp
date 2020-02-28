#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"


std::string test1 = "1,9,10,3,2,3,11,0,99,30,40,50";
std::string res1 = "3500,9,10,70,2,3,11,0,99,30,40,50";
std::string test2 = "1,0,0,0,99";
std::string res2 = "2,0,0,0,99";
std::string test3 = "2,3,0,3,99";
std::string res3 = "2,3,0,6,99";
std::string test4 = "2,4,4,5,99,0";
std::string res4 = "2,4,4,5,99,9801";
std::string test5 = "1,1,1,4,99,5,6,0,99";
std::string res5 = "30,1,1,4,2,5,6,0,99";

void runTest(std::string test, std::string res)
{
    Memory * testMem = new Memory(256);
    Memory * resMem = new Memory(256);
    MemoryLoader::LoadFromString(testMem, test);
    MemoryLoader::LoadFromString(resMem, res);
    testMem->dump(std::cout);
    
    ProgramRunner * runner = new ProgramRunner(testMem);
    int rc = runner->run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    if (testMem->getMaxUsedAddress() != resMem->getMaxUsedAddress())
    {
        std::cerr << "Test failed - max used address was " << testMem->getMaxUsedAddress() << "  expected " << resMem->getMaxUsedAddress() << std::endl;
        exit(1);
    }
    
    int testVal, resVal, i;
    for (i=0; i<testMem->getMaxUsedAddress(); i++)
    {
        testMem->get(i, &testVal);
        resMem->get(i, &resVal);
        if (testVal != resVal)
        {
            std::cerr << "Test failed - mismatch at " << i << "  expected " << resVal << " got " << testVal << std::endl;
            exit(1);
        }
    }
    std::cout << "Test passed - all " << i << " values matched" << std::endl;
    delete testMem;
    delete resMem;
    delete runner;
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
    std::cout << "Running test 3" << std::endl;
    runTest(test3, res3);
    std::cout << "Running test 4" << std::endl;
    runTest(test4, res4);
    std::cout << "Running test 5" << std::endl;
    runTest(test5, res5);
    
    return 0;
}
