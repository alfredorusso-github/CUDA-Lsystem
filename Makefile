CXX = nvcc

VPATH=./L-system/:./Examples/
INCLUDES=-I./L-system/
LSYSTEM=./L-system/
EXAMPLES=./Examples/

EXAMPLES_SRC = $(wildcard $(EXAMPLES)*.cpp)
EXAMPLES_OUT = $(patsubst $(EXAMPLES)%.cpp, $(EXAMPLES)%.out, $(EXAMPLES_SRC))

.PHONY: all clean

all: $(EXAMPLES_OUT)

$(EXAMPLES)%.out: $(EXAMPLES)%.cpp $(LSYSTEM)lsystem.o
	$(CXX) $(INCLUDES) $< $(LSYSTEM)lsystem.o -o $@

$(LSYSTEM)lsystem.o: $(LSYSTEM)lsystem.cu $(LSYSTEM)lsystem.h
	$(CXX) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(LSYSTEM)*.o $(EXAMPLES)*.out
