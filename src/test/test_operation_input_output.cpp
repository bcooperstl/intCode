#include <iostream>
#include <cstring>

#include "memory_loader.h"
#include "memory.h"
#include "input.h"
#include "output.h"

// this test says to input to memory 0 and then output memory 0
std::string test1 = "3, 0, 4, 0, 99";

void testInputOutput()
{
    Memory mem(256);
    Input input;
    Output output;
    MemoryLoader::LoadFromString(&mem, test1);

    std::cout << "Running " << input.getName() << " with opCode " << input.getOpcode() << std::endl;    
    int res = input.performOperation(&mem, 0, input.getOpcode());
    std::cout << "performOperation Result is " << res << std::endl;

    std::cout << "Running " << output.getName() << " with opCode " << output.getOpcode() << std::endl;    
    res = output.performOperation(&mem, 2, output.getOpcode());
    std::cout << "performOperation Result is " << res << std::endl;
    
    mem.dump(std::cout);
}

int main (int argc, char * argv[])
{
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << std::endl;
        return 1;
    }

    testInputOutput();
    return 0;
}
