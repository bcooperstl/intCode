CPPFLAGS=-Iinclude/core -Iinclude/common

build/core/memory.o: src/core/memory.cpp include/core/memory.h include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory.o -c src/core/memory.cpp

build/core/memory_loader.o: src/core/memory_loader.cpp include/core/memory_loader.h include/core/memory.h include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory_loader.o -c src/core/memory_loader.cpp

build/test/test_memoryloader.o: src/test/test_memoryloader.cpp include/core/memory_loader.h include/core/memory.h
	g++ ${CPPFLAGS} -o build/test/test_memoryloader.o -c src/test/test_memoryloader.cpp
    
bin/test/test_memoryloader: build/test/test_memoryloader.o build/core/memory_loader.o build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_memory_loader build/test/test_memoryloader.o build/core/memory_loader.o build/core/memory.o

clean:
	rm -f build/core/memory.o build/core/memory_loader.o build/test/test_memoryloader.o bin/test/test_memoryloader

all: build/core/memory.o build/core/memory_loader.o build/test/test_memoryloader.o bin/test/test_memoryloader
