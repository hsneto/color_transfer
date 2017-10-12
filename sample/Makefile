COMPILER = g++
FLAGS = -std=c++14

SO_DEPS = $(shell pkg-config --libs opencv)
SO_DEPS += -lboost_program_options

all: color_transfer

clean:
	rm color_transfer

color_transfer: color_transfer.cpp 
	$(COMPILER) $^ -o $@ $(FLAGS) $(SO_DEPS)
