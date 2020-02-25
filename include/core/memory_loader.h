#ifndef __MEMORY_LOADER_H__
#define __MEMORY_LOADER_H__

#include <iostream>
#include <sstream>
#include <string>
//#include "constants.h"
#include "memory.h"

class MemoryLoader
{
private:
    static int Load(Memory * m, std::istream * input);
public:
	static int LoadFromFile(Memory * m, std::string filename);
	static int LoadFromString(Memory * m, std::string input);
};

#endif
