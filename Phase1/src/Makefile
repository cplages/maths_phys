cc= g++
CFLAGS= -Wall 
SRC=vector3D.cpp particule.cpp
OBJ=vector3D.o particule.o

all: compile

compile: $(OBJ)

%.o: %.c
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm $(OBJ)
	rm *~
	rm *#
