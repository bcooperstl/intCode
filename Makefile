CPPFLAGS=-Iinclude/operations -Iinclude/core -Iinclude/common -Iinclude/programs

.DEFAULT_GOAL := all

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

build/operations/input.o: src/operations/input.cpp  \
	include/operations/input.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/input.o -c src/operations/input.cpp

build/operations/output.o: src/operations/output.cpp  \
	include/operations/output.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/output.o -c src/operations/output.cpp

build/operations/jump_if_true.o: src/operations/jump_if_true.cpp  \
	include/operations/jump_if_true.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/jump_if_true.o -c src/operations/jump_if_true.cpp

build/operations/jump_if_false.o: src/operations/jump_if_false.cpp  \
	include/operations/jump_if_false.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/jump_if_false.o -c src/operations/jump_if_false.cpp

build/operations/less_than.o: src/operations/less_than.cpp  \
	include/operations/less_than.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/less_than.o -c src/operations/less_than.cpp

build/operations/equals.o: src/operations/equals.cpp  \
	include/operations/equals.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/equals.o -c src/operations/equals.cpp

build/operations/operations_manager.o: src/operations/operations_manager.cpp  \
	include/operations/operations_manager.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/operations_manager.o -c src/operations/operations_manager.cpp

build/programs/program_runner.o: src/programs/program_runner.cpp \
	include/core/memory.h \
	include/common/constants.h \
	include/operations/addition.h  \
	include/operations/multiplication.h  \
	include/operations/input.h  \
	include/operations/output.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/programs/program_runner.o -c src/programs/program_runner.cpp

build/programs/day2_part1.o: src/programs/day2_part1.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
    include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/programs/day2_part1.o -c src/programs/day2_part1.cpp

build/programs/day2_part2.o: src/programs/day2_part2.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
    include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/programs/day2_part2.o -c src/programs/day2_part2.cpp

build/programs/day5_part1.o: src/programs/day5_part1.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
    include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/programs/day5_part1.o -c src/programs/day5_part1.cpp

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
    
build/test/test_operation_input_output.o: src/test/test_operation_input_output.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/operations/input.h  \
	include/operations/output.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/test/test_operation_input_output.o -c src/test/test_operation_input_output.cpp

build/test/test_day2_examples.o: src/test/test_day2_examples.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/operations/addition.h  \
	include/operations/multiplication.h  \
	include/operations/operation.h \
    include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/test/test_day2_examples.o -c src/test/test_day2_examples.cpp
    
build/test/test_day5_examples.o: src/test/test_day5_examples.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
    include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/test/test_day5_examples.o -c src/test/test_day5_examples.cpp
    
bin/lib/liboperations.a: build/operations/operation.o  \
	build/operations/addition.o  \
	build/operations/multiplication.o  \
	build/operations/input.o  \
	build/operations/output.o  \
	build/operations/jump_if_true.o  \
	build/operations/jump_if_false.o  \
	build/operations/less_than.o  \
	build/operations/equals.o  \
	build/operations/operations_manager.o
	ar rcs bin/lib/liboperations.a build/operations/operation.o build/operations/addition.o build/operations/multiplication.o build/operations/input.o build/operations/output.o build/operations/operations_manager.o

bin/programs/day2_part1: build/programs/day2_part1.o  \
	bin/lib/liboperations.a \
	build/core/memory_loader.o  \
	build/core/memory.o  \
	build/programs/program_runner.o
	g++ ${CPPFLAGS} -o bin/programs/day2_part1 build/programs/day2_part1.o build/core/memory_loader.o build/core/memory.o build/programs/program_runner.o -Lbin/lib -loperations

bin/programs/day2_part2: build/programs/day2_part2.o  \
	bin/lib/liboperations.a  \
	build/core/memory_loader.o  \
	build/core/memory.o  \
	build/programs/program_runner.o
	g++ ${CPPFLAGS} -o bin/programs/day2_part2 build/programs/day2_part2.o build/core/memory_loader.o build/core/memory.o build/programs/program_runner.o -Lbin/lib -loperations

bin/programs/day5_part1: build/programs/day5_part1.o  \
	bin/lib/liboperations.a  \
	build/core/memory_loader.o  \
	build/core/memory.o  \
	build/programs/program_runner.o
	g++ ${CPPFLAGS} -o bin/programs/day5_part1 build/programs/day5_part1.o build/core/memory_loader.o build/core/memory.o build/programs/program_runner.o -Lbin/lib -loperations

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

bin/test/test_operation_input_output: build/test/test_operation_input_output.o  \
	build/operations/input.o  \
	build/operations/output.o  \
	build/operations/operation.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_operation_input_output build/test/test_operation_input_output.o build/operations/input.o build/operations/output.o build/operations/operation.o build/core/memory_loader.o build/core/memory.o

bin/test/test_day2_examples: build/test/test_day2_examples.o  \
	bin/lib/liboperations.a \
	build/core/memory_loader.o  \
	build/core/memory.o  \
	build/programs/program_runner.o
	g++ ${CPPFLAGS} -o bin/test/test_day2_examples build/test/test_day2_examples.o build/core/memory_loader.o build/core/memory.o build/programs/program_runner.o -Lbin/lib -loperations

bin/test/test_day5_examples: build/test/test_day5_examples.o  \
	bin/lib/liboperations.a  \
	build/core/memory_loader.o  \
	build/core/memory.o  \
	build/programs/program_runner.o
	g++ ${CPPFLAGS} -o bin/test/test_day5_examples build/test/test_day5_examples.o build/core/memory_loader.o build/core/memory.o build/programs/program_runner.o -Lbin/lib -loperations

clean:
	rm -f build/core/memory.o  \
	build/core/memory_loader.o  \
	build/operations/operation.o  \
	build/operations/operations_manager.o  \
	build/operations/addition.o  \
	build/operations/multiplication.o  \
	build/operations/input.o  \
	build/operations/output.o  \
	build/operations/jump_if_true.o  \
	build/operations/jump_if_false.o  \
	build/operations/less_than.o  \
	build/operations/equals.o  \
	build/programs/program_runner.o  \
	build/programs/day2_part1.o  \
	build/programs/day2_part2.o  \
	build/programs/day5_part1.o  \
	build/test/test_memoryloader.o  \
	build/test/test_operation_addition.o  \
	build/test/test_operation_multiplication.o  \
	build/test/test_operation_input_output.o  \
	build/test/test_day2_examples.o  \
	build/test/test_day5_examples.o  \
	bin/lib/liboperations.a  \
	bin/programs/day2_part1 \
	bin/programs/day2_part2 \
	bin/programs/day5_part1 \
	bin/test/test_memoryloader \
	bin/test/test_operation_addition \
	bin/test/test_operation_multiplication \
	bin/test/test_operation_input_output \
	bin/test/test_day2_examples \
	bin/test/test_day5_examples

all: build/core/memory.o  \
	build/core/memory_loader.o  \
	build/operations/operation.o  \
	build/operations/operations_manager.o  \
	build/operations/addition.o  \
	build/operations/multiplication.o  \
	build/operations/input.o  \
	build/operations/output.o  \
	build/operations/jump_if_true.o  \
	build/operations/jump_if_false.o  \
	build/operations/less_than.o  \
	build/operations/equals.o  \
	build/programs/program_runner.o  \
	build/programs/day2_part1.o  \
	build/programs/day2_part2.o  \
	build/programs/day5_part1.o  \
	build/test/test_memoryloader.o  \
	build/test/test_operation_addition.o  \
	build/test/test_operation_multiplication.o  \
	build/test/test_operation_input_output.o  \
	build/test/test_day2_examples.o  \
	build/test/test_day5_examples.o  \
	bin/lib/liboperations.a  \
	bin/programs/day2_part1 \
	bin/programs/day2_part2 \
	bin/programs/day5_part1 \
	bin/test/test_memoryloader \
	bin/test/test_operation_addition \
	bin/test/test_operation_multiplication \
	bin/test/test_operation_input_output \
	bin/test/test_day2_examples \
	bin/test/test_day5_examples
