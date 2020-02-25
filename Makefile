CPPFLAGS=-Iinclude/core -Iinclude/common

src/core/memory.o: src/core/memory.cpp include/core/memory.h include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory.o -c src/core/memory.cpp

src/core/memory_loader.o: src/core/memory_loader.cpp include/core/memory_loader.h include/core/memory.h include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory_loader.o -c src/core/memory_loader.cpp

clean:
	rm -f build/core/memory.o build/core/memory_loader.o

all: src/core/memory.o src/core/memory_loader.o
