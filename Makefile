DEBUG=
#DEBUG+= -DDEBUG_MEMORY
#DEBUG+= -DDEBUG_OPERATIONS
#DEBUG+= -DDEBUG_OPERATIONS_MEMORY
#DEBUG+= -DDEBUG_PROGRAMS
#DEBUG+= -DDEBUG_SCREEN
CPPFLAGS=-g ${DEBUG} -Iinclude/core -Iinclude/common -Iinclude/operations -Iinclude/programs

.DEFAULT_GOAL := all

build/core/memory_page.o: src/core/memory_page.cpp  \
	include/core/memory_page.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory_page.o -c src/core/memory_page.cpp

build/core/memory.o: src/core/memory.cpp  \
	include/core/memory.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory.o -c src/core/memory.cpp

build/core/memory_loader.o: src/core/memory_loader.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/memory_loader.o -c src/core/memory_loader.cpp

build/core/inputter_outputter.o: src/core/inputter_outputter.cpp \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/inputter_outputter.o -c src/core/inputter_outputter.cpp

build/core/ascii_inputter_outputter.o: src/core/ascii_inputter_outputter.cpp \
	include/core/ascii_inputter_outputter.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/ascii_inputter_outputter.o -c src/core/ascii_inputter_outputter.cpp

build/core/tile.o: src/core/tile.cpp \
	include/core/tile.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/tile.o -c src/core/tile.cpp

build/core/screen.o: src/core/screen.cpp \
	include/core/screen.h \
	include/core/tile.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/core/screen.o -c src/core/screen.cpp

build/core/segment_display.o: src/core/segment_display.cpp \
	include/core/segment_display.h
	g++ ${CPPFLAGS} -o build/core/segment_display.o -c src/core/segment_display.cpp

build/core/joystick.o: src/core/joystick.cpp \
	include/core/joystick.h
	g++ ${CPPFLAGS} -o build/core/joystick.o -c src/core/joystick.cpp

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

build/operations/adjust_relative_base.o: src/operations/adjust_relative_base.cpp  \
	include/operations/adjust_relative_base.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/adjust_relative_base.o -c src/operations/adjust_relative_base.cpp

build/operations/operations_manager.o: src/operations/operations_manager.cpp  \
	include/operations/operations_manager.h  \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/operations/operations_manager.o -c src/operations/operations_manager.cpp

build/programs/runner.o: src/programs/runner.cpp \
	include/programs/runner.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/programs/runner.o -c src/programs/runner.cpp

build/programs/program_runner.o: src/programs/program_runner.cpp \
	include/core/memory.h \
	include/common/constants.h \
	include/operations/operation.h
	g++ ${CPPFLAGS} -o build/programs/program_runner.o -c src/programs/program_runner.cpp

build/programs/program_manager.o: src/programs/program_manager.cpp \
	include/programs/program_runner.h \
	include/common/constants.h
	g++ ${CPPFLAGS} -o build/programs/program_manager.o -c src/programs/program_manager.cpp

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

build/programs/day7_part1.o: src/programs/day7_part1.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/programs/day7_part1.o -c src/programs/day7_part1.cpp

build/programs/day7_part1_mgr.o: src/programs/day7_part1_mgr.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h \
	include/programs/program_manager.h
	g++ ${CPPFLAGS} -o build/programs/day7_part1_mgr.o -c src/programs/day7_part1_mgr.cpp

build/programs/day7_part2.o: src/programs/day7_part2.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h \
	include/programs/program_manager.h
	g++ ${CPPFLAGS} -o build/programs/day7_part2.o -c src/programs/day7_part2.cpp

build/programs/day9_part1.o: src/programs/day9_part1.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h \
	include/programs/program_manager.h
	g++ ${CPPFLAGS} -o build/programs/day9_part1.o -c src/programs/day9_part1.cpp

build/programs/day9_part2.o: src/programs/day9_part2.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h \
	include/programs/program_manager.h
	g++ ${CPPFLAGS} -o build/programs/day9_part2.o -c src/programs/day9_part2.cpp

build/programs/day11_panel.o: src/programs/day11_panel.cpp  \
	include/programs/day11_panel.h
	g++ ${CPPFLAGS} -o build/programs/day11_panel.o -c src/programs/day11_panel.cpp

build/programs/day11_side.o: src/programs/day11_side.cpp  \
	include/programs/day11_panel.h \
	include/programs/day11_side.h
	g++ ${CPPFLAGS} -o build/programs/day11_side.o -c src/programs/day11_side.cpp

build/programs/day11_runner.o: src/programs/day11_runner.cpp  \
	include/programs/day11_runner.h \
	include/programs/day11_panel.h \
	include/programs/day11_side.h
	g++ ${CPPFLAGS} -o build/programs/day11_runner.o -c src/programs/day11_runner.cpp

build/programs/day11_part1.o: src/programs/day11_part1.cpp  \
	include/programs/day11_runner.h \
	include/programs/day11_panel.h \
	include/programs/day11_side.h
	g++ ${CPPFLAGS} -o build/programs/day11_part1.o -c src/programs/day11_part1.cpp

build/programs/day11_part2.o: src/programs/day11_part2.cpp  \
	include/programs/day11_runner.h \
	include/programs/day11_panel.h \
	include/programs/day11_side.h
	g++ ${CPPFLAGS} -o build/programs/day11_part2.o -c src/programs/day11_part2.cpp

build/programs/day13_part1_runner.o: src/programs/day13_part1_runner.cpp  \
	include/programs/day13_part1_runner.h
	g++ ${CPPFLAGS} -o build/programs/day13_part1_runner.o -c src/programs/day13_part1_runner.cpp

build/programs/day13_part1.o: src/programs/day13_part1.cpp  \
	include/programs/day13_part1_runner.h
	g++ ${CPPFLAGS} -o build/programs/day13_part1.o -c src/programs/day13_part1.cpp

build/programs/day13_part2_runner.o: src/programs/day13_part2_runner.cpp  \
	include/programs/day13_part2_runner.h
	g++ ${CPPFLAGS} -o build/programs/day13_part2_runner.o -c src/programs/day13_part2_runner.cpp

build/programs/day13_part2.o: src/programs/day13_part2.cpp  \
	include/programs/day13_part2_runner.h
	g++ ${CPPFLAGS} -o build/programs/day13_part2.o -c src/programs/day13_part2.cpp

build/programs/day15_point.o: src/programs/day15_point.cpp  \
	include/programs/day15_point.h
	g++ ${CPPFLAGS} -o build/programs/day15_point.o -c src/programs/day15_point.cpp

build/programs/day15_area.o: src/programs/day15_area.cpp  \
	include/programs/day15_area.h \
	include/programs/day15_point.h
	g++ ${CPPFLAGS} -o build/programs/day15_area.o -c src/programs/day15_area.cpp

build/programs/day15_runner.o: src/programs/day15_runner.cpp  \
	include/programs/day15_runner.h \
	include/programs/day15_area.h \
	include/programs/day15_point.h
	g++ ${CPPFLAGS} -o build/programs/day15_runner.o -c src/programs/day15_runner.cpp

build/programs/day15_part1.o: src/programs/day15_part1.cpp  \
	include/programs/day15_runner.h \
	include/programs/day15_area.h \
	include/programs/day15_point.h
	g++ ${CPPFLAGS} -o build/programs/day15_part1.o -c src/programs/day15_part1.cpp

build/programs/day15_part2.o: src/programs/day15_part2.cpp  \
	include/programs/day15_runner.h \
	include/programs/day15_area.h \
	include/programs/day15_point.h
	g++ ${CPPFLAGS} -o build/programs/day15_part2.o -c src/programs/day15_part2.cpp

build/programs/day17_part1_runner.o: src/programs/day17_part1_runner.cpp  \
	include/programs/day17_part1_runner.h
	g++ ${CPPFLAGS} -o build/programs/day17_part1_runner.o -c src/programs/day17_part1_runner.cpp

build/programs/day17_part1.o: src/programs/day17_part1.cpp  \
	include/programs/day17_part1_runner.h
	g++ ${CPPFLAGS} -o build/programs/day17_part1.o -c src/programs/day17_part1.cpp

build/programs/day17_part2_runner.o: src/programs/day17_part2_runner.cpp  \
	include/programs/day17_part2_runner.h
	g++ ${CPPFLAGS} -o build/programs/day17_part2_runner.o -c src/programs/day17_part2_runner.cpp

build/programs/day17_part2.o: src/programs/day17_part2.cpp  \
	include/programs/day17_part2_runner.h
	g++ ${CPPFLAGS} -o build/programs/day17_part2.o -c src/programs/day17_part2.cpp

build/programs/day19_part1.o: src/programs/day19_part1.cpp
	g++ ${CPPFLAGS} -o build/programs/day19_part1.o -c src/programs/day19_part1.cpp

build/programs/day19_part2.o: src/programs/day19_part2.cpp
	g++ ${CPPFLAGS} -o build/programs/day19_part2.o -c src/programs/day19_part2.cpp

build/programs/day21_part1.o: src/programs/day21_part1.cpp
	g++ ${CPPFLAGS} -o build/programs/day21_part1.o -c src/programs/day21_part1.cpp

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
	
build/test/test_day5_part2_examples.o: src/test/test_day5_part2_examples.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/test/test_day5_part2_examples.o -c src/test/test_day5_part2_examples.cpp
	
build/test/test_day9_examples.o: src/test/test_day9_examples.cpp  \
	include/core/memory_loader.h  \
	include/core/memory.h  \
	include/programs/program_runner.h
	g++ ${CPPFLAGS} -o build/test/test_day9_examples.o -c src/test/test_day9_examples.cpp
	
bin/lib/libcore.a: build/core/memory_page.o  \
	build/core/memory.o  \
	build/core/memory_loader.o  \
	build/core/inputter_outputter.o  \
	build/core/ascii_inputter_outputter.o  \
	build/core/tile.o  \
	build/core/screen.o  \
	build/core/segment_display.o  \
	build/core/joystick.o
	ar rcs bin/lib/libcore.a build/core/memory_page.o build/core/memory.o build/core/memory_loader.o build/core/inputter_outputter.o build/core/ascii_inputter_outputter.o build/core/tile.o build/core/screen.o build/core/segment_display.o build/core/joystick.o

bin/lib/liboperations.a: build/operations/operation.o  \
	build/operations/addition.o  \
	build/operations/multiplication.o  \
	build/operations/input.o  \
	build/operations/output.o  \
	build/operations/jump_if_true.o  \
	build/operations/jump_if_false.o  \
	build/operations/less_than.o  \
	build/operations/equals.o  \
	build/operations/adjust_relative_base.o  \
	build/operations/operations_manager.o
	ar rcs bin/lib/liboperations.a build/operations/operation.o build/operations/addition.o build/operations/multiplication.o build/operations/input.o build/operations/output.o build/operations/jump_if_true.o build/operations/jump_if_false.o build/operations/less_than.o build/operations/equals.o build/operations/adjust_relative_base.o build/operations/operations_manager.o

bin/lib/libprograms.a : build/programs/runner.o  \
	build/programs/program_runner.o  \
	build/programs/program_manager.o
	ar rcs bin/lib/libprograms.a build/programs/runner.o build/programs/program_runner.o build/programs/program_manager.o

bin/programs/day2_part1: build/programs/day2_part1.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day2_part1 build/programs/day2_part1.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day2_part2: build/programs/day2_part2.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day2_part2 build/programs/day2_part2.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day5_part1: build/programs/day5_part1.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day5_part1 build/programs/day5_part1.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day7_part1: build/programs/day7_part1.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day7_part1 build/programs/day7_part1.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day7_part1_mgr: build/programs/day7_part1_mgr.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day7_part1_mgr build/programs/day7_part1_mgr.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day7_part2: build/programs/day7_part2.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day7_part2 build/programs/day7_part2.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day9_part1: build/programs/day9_part1.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day9_part1 build/programs/day9_part1.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day9_part2: build/programs/day9_part2.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day9_part2 build/programs/day9_part2.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day11_part1: build/programs/day11_part1.o  \
	build/programs/day11_runner.o  \
	build/programs/day11_side.o  \
	build/programs/day11_panel.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day11_part1 build/programs/day11_part1.o build/programs/day11_runner.o build/programs/day11_side.o build/programs/day11_panel.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day11_part2: build/programs/day11_part2.o  \
	build/programs/day11_runner.o  \
	build/programs/day11_side.o  \
	build/programs/day11_panel.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day11_part2 build/programs/day11_part2.o build/programs/day11_runner.o build/programs/day11_side.o build/programs/day11_panel.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day13_part1: build/programs/day13_part1.o  \
	build/programs/day13_part1_runner.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day13_part1 build/programs/day13_part1.o build/programs/day13_part1_runner.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day13_part2: build/programs/day13_part2.o  \
	build/programs/day13_part2_runner.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day13_part2 build/programs/day13_part2.o build/programs/day13_part2_runner.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day15_part1: build/programs/day15_part1.o  \
	build/programs/day15_point.o  \
	build/programs/day15_area.o  \
	build/programs/day15_runner.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day15_part1 build/programs/day15_part1.o build/programs/day15_point.o build/programs/day15_area.o build/programs/day15_runner.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day15_part2: build/programs/day15_part2.o  \
	build/programs/day15_point.o  \
	build/programs/day15_area.o  \
	build/programs/day15_runner.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day15_part2 build/programs/day15_part2.o build/programs/day15_point.o build/programs/day15_area.o build/programs/day15_runner.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day17_part1: build/programs/day17_part1.o  \
	build/programs/day17_part1_runner.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day17_part1 build/programs/day17_part1.o build/programs/day17_part1_runner.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day17_part2: build/programs/day17_part2.o  \
	build/programs/day17_part2_runner.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day17_part2 build/programs/day17_part2.o build/programs/day17_part2_runner.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day19_part1: build/programs/day19_part1.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day19_part1 build/programs/day19_part1.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day19_part2: build/programs/day19_part2.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day19_part2 build/programs/day19_part2.o -Lbin/lib -lprograms -loperations -lcore

bin/programs/day21_part1: build/programs/day21_part1.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/programs/day21_part1 build/programs/day21_part1.o -Lbin/lib -lprograms -loperations -lcore

bin/test/test_memoryloader: build/test/test_memoryloader.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_memoryloader build/test/test_memoryloader.o -Lbin/lib -lcore

bin/test/test_operation_addition: build/test/test_operation_addition.o  \
	build/operations/addition.o  \
	build/operations/operation.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_operation_addition build/test/test_operation_addition.o -Lbin/lib -loperations -lcore

bin/test/test_operation_multiplication: build/test/test_operation_multiplication.o  \
	build/operations/multiplication.o  \
	build/operations/operation.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_operation_multiplication build/test/test_operation_multiplication.o -Lbin/lib -loperations -lcore

bin/test/test_operation_input_output: build/test/test_operation_input_output.o  \
	build/operations/input.o  \
	build/operations/output.o  \
	build/operations/operation.o  \
	build/core/memory_loader.o  \
	build/core/memory.o
	g++ ${CPPFLAGS} -o bin/test/test_operation_input_output build/test/test_operation_input_output.o -Lbin/lib -loperations -lcore

bin/test/test_day2_examples: build/test/test_day2_examples.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/test/test_day2_examples build/test/test_day2_examples.o -Lbin/lib -lprograms -loperations -lcore

bin/test/test_day5_examples: build/test/test_day5_examples.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/test/test_day5_examples build/test/test_day5_examples.o -Lbin/lib -lprograms -loperations -lcore

bin/test/test_day5_part2_examples: build/test/test_day5_part2_examples.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/test/test_day5_part2_examples build/test/test_day5_part2_examples.o -Lbin/lib -lprograms -loperations -lcore

bin/test/test_day9_examples: build/test/test_day9_examples.o  \
	bin/lib/libcore.a \
	bin/lib/liboperations.a \
	bin/lib/libprograms.a
	g++ ${CPPFLAGS} -o bin/test/test_day9_examples build/test/test_day9_examples.o -Lbin/lib -lprograms -loperations -lcore

clean:
	rm -f build/core/memory_page.o  \
	build/core/memory.o  \
	build/core/memory_loader.o  \
	build/core/inputter_outputter.o  \
	build/core/ascii_inputter_outputter.o  \
	build/core/tile.o  \
	build/core/screen.o  \
	build/core/segment_display.o  \
	build/core/joystick.o  \
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
	build/operations/adjust_relative_base.o  \
	build/programs/runner.o  \
	build/programs/program_runner.o  \
	build/programs/program_manager.o  \
	build/programs/day2_part1.o  \
	build/programs/day2_part2.o  \
	build/programs/day5_part1.o  \
	build/programs/day7_part1.o  \
	build/programs/day7_part1_mgr.o  \
	build/programs/day7_part2.o  \
	build/programs/day9_part1.o  \
	build/programs/day9_part2.o  \
	build/programs/day11_panel.o  \
	build/programs/day11_side.o  \
	build/programs/day11_runner.o  \
	build/programs/day11_part1.o  \
	build/programs/day11_part2.o  \
	build/programs/day13_part1_runner.o  \
	build/programs/day13_part1.o  \
	build/programs/day13_part2_runner.o  \
	build/programs/day13_part2.o  \
	build/programs/day15_point.o  \
	build/programs/day15_area.o  \
	build/programs/day15_runner.o  \
	build/programs/day15_part1.o  \
	build/programs/day15_part2.o  \
	build/programs/day17_part1_runner.o  \
	build/programs/day17_part1.o  \
	build/programs/day17_part2_runner.o  \
	build/programs/day17_part2.o  \
	build/programs/day19_part1.o  \
	build/programs/day19_part2.o  \
	build/programs/day21_part1.o  \
	build/test/test_memoryloader.o  \
	build/test/test_operation_addition.o  \
	build/test/test_operation_multiplication.o  \
	build/test/test_operation_input_output.o  \
	build/test/test_day2_examples.o  \
	build/test/test_day5_examples.o  \
	build/test/test_day5_part2_examples.o  \
	build/test/test_day9_examples.o  \
	bin/lib/libcore.a  \
	bin/lib/liboperations.a  \
	bin/lib/libprograms.a  \
	bin/programs/day2_part1 \
	bin/programs/day2_part2 \
	bin/programs/day5_part1 \
	bin/programs/day7_part1 \
	bin/programs/day7_part1_mgr \
	bin/programs/day7_part2 \
	bin/programs/day9_part1 \
	bin/programs/day9_part2 \
	bin/programs/day11_part1 \
	bin/programs/day11_part2 \
	bin/programs/day13_part1 \
	bin/programs/day13_part2 \
	bin/programs/day15_part1 \
	bin/programs/day15_part2 \
	bin/programs/day17_part1 \
	bin/programs/day17_part2 \
	bin/programs/day19_part1 \
	bin/programs/day19_part2 \
	bin/programs/day21_part1 \
	bin/test/test_memoryloader \
	bin/test/test_operation_addition \
	bin/test/test_operation_multiplication \
	bin/test/test_operation_input_output \
	bin/test/test_day2_examples \
	bin/test/test_day5_examples \
	bin/test/test_day5_part2_examples \
	bin/test/test_day9_examples

all: build/core/memory_page.o  \
	build/core/memory.o  \
	build/core/memory_loader.o  \
	build/core/inputter_outputter.o  \
	build/core/ascii_inputter_outputter.o  \
	build/core/tile.o  \
	build/core/screen.o  \
	build/core/segment_display.o  \
	build/core/joystick.o  \
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
	build/operations/adjust_relative_base.o  \
	build/programs/runner.o  \
	build/programs/program_runner.o  \
	build/programs/program_manager.o  \
	build/programs/day2_part1.o  \
	build/programs/day2_part2.o  \
	build/programs/day5_part1.o  \
	build/programs/day7_part1.o  \
	build/programs/day7_part1_mgr.o  \
	build/programs/day7_part2.o  \
	build/programs/day9_part1.o  \
	build/programs/day9_part2.o  \
	build/programs/day11_panel.o  \
	build/programs/day11_side.o  \
	build/programs/day11_runner.o  \
	build/programs/day11_part1.o  \
	build/programs/day11_part2.o  \
	build/programs/day13_part1_runner.o  \
	build/programs/day13_part1.o  \
	build/programs/day13_part2_runner.o  \
	build/programs/day13_part2.o  \
	build/programs/day15_point.o  \
	build/programs/day15_area.o  \
	build/programs/day15_runner.o  \
	build/programs/day15_part1.o  \
	build/programs/day15_part2.o  \
	build/programs/day17_part1_runner.o  \
	build/programs/day17_part1.o  \
	build/programs/day17_part2_runner.o  \
	build/programs/day17_part2.o  \
	build/programs/day19_part1.o  \
	build/programs/day19_part2.o  \
	build/programs/day21_part1.o  \
	build/test/test_memoryloader.o  \
	build/test/test_operation_addition.o  \
	build/test/test_operation_multiplication.o  \
	build/test/test_operation_input_output.o  \
	build/test/test_day2_examples.o  \
	build/test/test_day5_examples.o  \
	bin/lib/libcore.a  \
	bin/lib/liboperations.a  \
	bin/lib/libprograms.a  \
	bin/programs/day2_part1 \
	bin/programs/day2_part2 \
	bin/programs/day5_part1 \
	bin/programs/day7_part1 \
	bin/programs/day7_part1_mgr \
	bin/programs/day7_part2 \
	bin/programs/day9_part1 \
	bin/programs/day9_part2 \
	bin/programs/day11_part1 \
	bin/programs/day11_part2 \
	bin/programs/day13_part1 \
	bin/programs/day13_part2 \
	bin/programs/day15_part1 \
	bin/programs/day15_part2 \
	bin/programs/day17_part1 \
	bin/programs/day17_part2 \
	bin/programs/day19_part1 \
	bin/programs/day19_part2 \
	bin/programs/day21_part1 \
	bin/test/test_operation_addition \
	bin/test/test_operation_multiplication \
	bin/test/test_operation_input_output \
	bin/test/test_day2_examples \
	bin/test/test_day5_examples \
	bin/test/test_day5_part2_examples \
	bin/test/test_day9_examples
