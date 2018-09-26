cc= g++
CFLAGS= -Wall 
SRC=vector3D.cpp particle.cpp force_register.cpp particle_drag_generator.cpp particle_gravity_generator.cpp particle_spring_generator.cpp particle_anchored_generator.cpp particle_bungee_generator.cpp particle_buoyancy_generator.cpp
OBJ=vector3D.o particle.o force_register.o particle_drag_generator.o particle_gravity_generator.o particle_spring_generator.o particle_anchored_generator.o particle_bungee_generator.o particle_buoyancy_generator.o

all: compile

compile: $(OBJ)

%.o: %.c
	$(cc) -c -o $@ $< $(CFlAGS)

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f *#
