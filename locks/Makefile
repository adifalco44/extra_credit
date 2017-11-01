CXX=       g++
CXXFLAGS= -g -gdwarf-2 -std=gnu++11 -Wall
LD=g++
LDFLAGS=-pthread
PROGRAMS=       $(C_SOURCE:.cpp=)
	TARGETS=main \
		main.o

all:    $(TARGETS)

main:main.o
	@$(LD) $(LDFLAGS) -o $@ main.o

main.o:main.cpp header.h thread.h 
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

clean:
	rm -f $(TARGETS)

.PHONY: all clean

