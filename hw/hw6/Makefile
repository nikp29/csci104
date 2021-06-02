CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

all: counting

counting: counting.o hashtable.o
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ counting.o hashtable.o

counting.o: counting.cpp Hashtable.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c counting.cpp
hashtable.o: Hashtable.cpp Hashtable.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Hashtable.cpp


clean:
	rm -f *.o hashtableTest
