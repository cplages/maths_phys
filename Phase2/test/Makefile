cc= g++
CFLAGS= -Wall
SRC=vector3D_test.cpp particle_test.cpp launcher.cpp
OBJ=vector3D_test.o particle_test.o launcher.o

LDEP=../src
DEP=$(wildcard $(LDEP)/*.o)

all:compile link run

reset_draw: clean draw
	./draw

compile: $(OBJ)

link: $(DEP) $(OBJ)
	g++ -o test $^
run: link
	./test

draw: $(DEP)
	g++ -o draw $^ particle_draw.cpp -lGLU -lGL -lglut


%.o: %.c
	$(cc) -c -o $@ $< $(CFlAGS)

$(DEP): $(patsubst %.o, %.cpp, $(DEP))
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm -f test
	rm -f draw
	rm -f $(DEP)
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
