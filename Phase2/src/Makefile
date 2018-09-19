cc= g++
CFLAGS= -Wall 
SRC=vector3D.cpp particule.cpp force_register.cpp
OBJ=vector3D.o particule.o force_register.o

all: compile

compile: $(OBJ)

%.o: %.c
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm $(OBJ)
	rm *~
	rm *#
