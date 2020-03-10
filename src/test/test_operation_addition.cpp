#include <iostream>
#include <cstring>

#include "memory_loader.h"
#include "memory.h"
#include "addition.h"

// this test says to add the values at positions 4 and 5 (i.e. the 10 and 20) and store them in position 6 (overwriting the 99 with 0);
std::string test1 = "1, 4, 5, 6, 10, 20, 99, 0";
int res_position=6;
int expected_res=30;

void testAddition()
{
    long new_ip;
    Memory * mem = new Memory(256);
    Addition * addition = new Addition();
    MemoryLoader::LoadFromString(mem, test1);
    std::cout << "Running " << addition->getName() << " with opCode " << addition->getOpcode() << std::endl;
    int res = addition->performOperation(mem, 0, addition->getOpcode(), &new_ip, NULL, NULL);
    std::cout << "performOperation Result is " << res << std::endl;
    int actual_res=0;
    mem->getImmediateMode(res_position, &actual_res);
    if (expected_res == actual_res)
    {
        std::cout << "Result matches " << actual_res << std::endl;
    }
    else
    {
        std::cout << "******Result mismatch expected " << expected_res << " received " << actual_res << std::endl;   
    }
    if (new_ip!=4)
    {
        std::cout << "******New IP mismatch. expected 4 received " << new_ip << std::endl;
    }
    mem->dump(std::cout);
    delete addition;
    delete mem;
}

int main (int argc, char * argv[])
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    testAddition();
    return 0;
}
