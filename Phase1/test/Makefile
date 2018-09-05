cc= g++
CFLAGS= -Wall
SRC=vector3D_test.cpp particule_test.cpp launcher.cpp
OBJ=vector3D_test.o particule_test.o launcher.o

NDEP=vector3D.o particule.o
LDEP=../src
DEP = $(patsubst %,$(LDEP)/%,$(NDEP))

all:compile link run

compile: $(OBJ)

link: $(DEP) $(OBJ)
	g++ -o test $^
run: link
	./test

%.o: %.c
	$(cc) -c -o $@ $< $(CFlAGS)

$(LDEP)/%.o: $(LDEP)/%.c
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm test
	rm $(DEP)
	rm $(OBJ)
