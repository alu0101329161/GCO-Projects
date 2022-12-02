# COMPILER= g++ -w
# OPTIONS= -std=c++11 -Wall

# sitema_bc: main.cc
# 	$(COMPILER) $(OPTIONS) main.cc sistema.cc file_control.cc file.cc -o main


CXX = g++
CXXFLAGS = -g -w
NAMEGLAGS = -o
SRC = main.cc sistema.cc file_control.cc file.cc usage.cc -o main
PROGRAM_NAME = main

make:
	$(CXX) $(CXXFLAGS) $(SRC) $(NAMEGLAGS) $(PROGRAM_NAME)

.PHONY: all clean

	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm -f $(PROGRAM_NAME) *.o
	rm -rf *~ basura b i