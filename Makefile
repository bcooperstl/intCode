CPPFLAGS=-Iinclude/core -Iinclude/common

src/core/memory.o: src/core/memory.cpp include/core/memory.h include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory.o -c src/core/memory.cpp
