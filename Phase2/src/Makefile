cc= g++
CFLAGS= -Wall
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

all: compile

compile: $(OBJ)

%.o: %.cpp
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
