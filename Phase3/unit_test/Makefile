cc= g++
CFLAGS= -Wall

SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

LDEP=../src
DEP=$(patsubst %.cpp, %.o, $(wildcard $(LDEP)/*.cpp))

all: compile run

compile: $(OBJ)

run: compile $(DEP)
	g++ $(OBJ) $(DEP) -Wall -o unit_test

%.o: %.cpp
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm -f $(DEP)
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
