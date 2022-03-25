TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
ALL_SRCS := $(wildcard *.cpp)
SRCS     := $(filter-out check.cpp, $(ALL_SRCS))

all: compile test check

compilerun: compile run

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 -o main main.cpp src/Config.cpp src/CraftingTable.cpp src/Inventory.cpp src/Item.cpp src/Nontool.cpp src/Recipe.cpp src/Tool.cpp

# Test
test: 
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

# Check
check: FORCE check.cpp
	g++ -std=c++17 -o check check.cpp
	./check

run: 
	./main

FORCE: ;