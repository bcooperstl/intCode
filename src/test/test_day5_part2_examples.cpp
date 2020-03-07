#include <iostream>
#include <cstring>

#include "constants.h"

#include "memory_loader.h"
#include "memory.h"
#include "program_runner.h"


std::string eq8_1 = "3,9,8,9,10,9,4,9,99,-1,8";
std::string lt8_1 = "3,9,7,9,10,9,4,9,99,-1,8";
std::string eq8_2 = "3,3,1108,-1,8,3,4,3,99";
std::string lt8_2 = "3,3,1107,-1,8,3,4,3,99";
std::string jump1 = "3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9";
std::string jump2 = "3,3,1105,-1,9,1101,0,0,12,4,12,99,1";
std::string longTest = "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99";

void runTest_eq(std::string test)
{
    int rc;
    Memory testMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    testMem.dump(std::cout);
    
    ProgramRunner runner(&testMem);
    std::cout << "This program tests for if a number equals 8. In this run, give 8 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 1 to indicate equals." << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number equals 8. In this run, give 7 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 0 to indicate non-equals." << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number equals 8. In this run, give 9 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 0 to indicate non-equals" << std::endl;
}

void runTest_lt(std::string test)
{
    int rc;
    Memory testMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    testMem.dump(std::cout);
    
    ProgramRunner runner(&testMem);
    std::cout << "This program tests for if a number is less than 8. In this run, give 7 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 1 to indicate 7 is less than 8." << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number is less than 8. In this run, give 8 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 0 to indicate that 8 is not less than 8" << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number is less than 8. In this run, give 9 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 0 to indicate 9 is not less than 8" << std::endl;
}

void runTest_j(std::string test)
{
    int rc;
    Memory testMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    testMem.dump(std::cout);
    
    ProgramRunner runner(&testMem);
    std::cout << "This program tests for if a number is 0. In this run, give 0 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 0 to indicate the input was 0." << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number is 0. In this run, give 45 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 1 to indicate the input was non-zero." << std::endl;
}

void runTest_long(std::string test)
{
    int rc;
    Memory testMem(256);
    MemoryLoader::LoadFromString(&testMem, test);
    testMem.dump(std::cout);
    
    ProgramRunner runner(&testMem);
    std::cout << "This is the long test. In this run, give 8 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 1000 to indicate equals 8." << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number equals 8. In this run, give 7 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 999 to indicate less than 8." << std::endl;
    
    MemoryLoader::LoadFromString(&testMem, test);

    std::cout << "This program tests for if a number equals 8. In this run, give 9 as the input" << std::endl;
    
    rc = runner.run();
    if (rc != SUCCESS)
    {
        std::cerr << "Test failed with error " << rc << std::endl;
        exit(1);
    }
    
    std::cout << "Compare that the above output matches 1001 to indicate greater than 8" << std::endl;
}

int main (int argc, char * argv[])
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    runTest_eq(eq8_1);
    runTest_eq(eq8_2);
    runTest_lt(lt8_1);
    runTest_lt(lt8_2);
    runTest_j(jump1);
    runTest_j(jump2);
    runTest_long(longTest);
    
    
    return 0;
}
