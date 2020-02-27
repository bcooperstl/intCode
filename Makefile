CPPFLAGS=-Iinclude/operations -Iinclude/core -Iinclude/common

build/core/memory.o: src/core/memory.cpp  \
	include/core/memory.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory.o -c src/core/memory.cpp

build/core/memory_loader.o: src/core/memory_loader.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory_loader.o -c src/core/memory_loader.cpp

build/operations/operation.o: src/operations/operation.cpp  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/operation.o -c src/operations/operation.cpp

build/operations/addition.o: src/operations/addition.cpp  \
	include/operations/addition.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/addition.o -c src/operations/addition.cpp

build/operations/multiplication.o: src/operations/multiplication.cpp  \
	include/operations/multiplication.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/multiplication.o -c src/operations/multiplication.cpp

build/test/test_memoryloader.o: src/test/test_memoryloader.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h
	g++ ${CPPFLAGS} -o build/test/test_memoryloader.o -c src/test/test_memoryloader.cpp
    
build/test/test_operation_addition.o: src/test/test_operation_addition.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/operations/addition.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/test/test_operation_addition.o -c src/test/test_operation_addition.cpp
    
build/test/test_operation_multiplication.o: src/test/test_operation_multiplication.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/operations/multiplication.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/test/test_operation_multiplication.o -c src/test/test_operation_multiplication.cpp
    
bin/test/test_memoryloader: build/test/test_memoryloader.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_memoryloader build/test/test_memoryloader.o build/core/memory_loader.o build/core/memory.o

bin/test/test_operation_addition: build/test/test_operation_addition.o  \
	build/operations/addition.o  \
	build/operations/operation.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_operation_addition build/test/test_operation_addition.o build/operations/addition.o build/operations/operation.o build/core/memory_loader.o build/core/memory.o

bin/test/test_operation_multiplication: build/test/test_operation_multiplication.o  \
	build/operations/multiplication.o  \
	build/operations/operation.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_operation_multiplication build/test/test_operation_multiplication.o build/operations/multiplication.o build/operations/operation.o build/core/memory_loader.o build/core/memory.o

clean:
	rm -f build/core/memory.o  \
	build/core/memory_loader.o  \
	build/operations/operation.o  \
	build/operations/addition.o  \
	build/operations/multiplication.o  \
	build/test/test_memoryloader.o  \
	build/test/test_operation_addition.o  \
	build/test/test_operation_multiplication.o  \
	bin/test/test_memoryloader \
	bin/test/test_operation_addition \
	bin/test/test_operation_multiplication

all: build/core/memory.o  \
	build/core/memory_loader.o  \
	build/operations/operation.o  \
	build/operations/addition.o  \
	build/operations/multiplication.o  \
	build/test/test_memoryloader.o  \
	build/test/test_operation_addition.o  \
	build/test/test_operation_multiplication.o  \
	bin/test/test_memoryloader \
	bin/test/test_operation_addition \
	bin/test/test_operation_multiplication
