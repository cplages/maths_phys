cc= g++
CFLAGS= -Wall
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, %.o, $(SRC))

LDEP=../src
DEP=$(patsubst %.cpp, %.o, $(wildcard $(LDEP)/*.cpp))

all:compile link run

reset_draw: clean draw
	./draw

compile: $(OBJ)

link: $(OBJ) $(DEP)
	g++ -o test $^ -lGLU -lGL -lglut -lGLEW
run: link
	./test


%.o: %.cpp
	$(cc) -c -o $@ $< $(CFlAGS)


clean:
	rm -f test
	rm -f draw
	rm -f $(DEP)
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
