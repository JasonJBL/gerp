###
### Makefile for gerp Project
###
### Authors: Jason Singer and Jake Merritt


MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


gerp: main.o gerpHash.o stringProcessing.o gerp.o toLower.o  DirNode.o FSTree.o
	$(CXX) $(LDFLAGS) -O2 -o gerp main.o DirNode.o FSTree.o toLower.o gerpHash.o gerp.o stringProcessing.o

main.o: main.cpp gerp.h gerpHash.h stringProcessing.h toLower.h FSTree.h DirNode.h 
	$(CXX) $(CXXFLAGS) main.cpp -c

gerp.o: gerp.cpp gerp.h gerpHash.h stringProcessing.h toLower.h FSTree.h DirNode.h 
	$(CXX) $(CXXFLAGS) gerp.cpp -c

unit_test: unit_test_driver.o stringProcessing.o  gerpHash.o toLower.o 
	$(CXX) $(CXXFLAGS) $^

stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) stringProcessing.cpp -c

FSTreeTraversal.o: FSTreeTraversal.cpp FSTree.h DirNode.h
	$(CXX) $(CXXFLAGS) FSTreeTraversal.cpp -c

gerpHash.o: gerpHash.cpp gerpHash.h toLower.h
	$(CXX) $(CXXFLAGS) gerpHash.cpp -c

toLower.o: toLower.cpp toLower.h
	$(CXX) $(CXXFLAGS) toLower.cpp -c

