#include "rigidbody.hpp"
#include "primitive.hpp"
#include "plane.hpp"
#include <stdio.h>

Plane::Plane():Primitive() {
}

Plane::Plane(Rigidbody * r0, float width, float height, float deepness):Primitive(r0) {
  half_size = Vector3D(width/2, height/2, deepness/2);
  calculate_vertex_coordinate();
}

void Plane::calculate_vertex_coordinate() {
  vertex = new Vector3D[8];
  float current_x = 0;
  float current_y = 0;
  float current_z = 0;
  for(int i = 0; i < 2; ++i) {
    current_x =  -half_size.get_x() + i * half_size.get_x() * 2;
    for(int j = 0; j < 2; ++j) {
      current_y =  -half_size.get_y() + j * half_size.get_y() * 2;
      for(int k = 0; k < 2; ++k) {
	current_z =  -half_size.get_z() + k * half_size.get_z() * 2;
	int index = i * 4 + j * 2 + k;
	vertex[index] = Vector3D(current_x, current_y, current_z);
      }
    }
  }
}


Vector3D Plane::get_half_size() {
  return half_size;
}


Vector3D * Plane::get_vertex() {
  return vertex;
}

void Plane::display_vertex() {
  printf("Plane: \n");
  for(int i = 0; i < 8; ++i) {
    printf("vertex: %d\n", i);
    vertex[i].display();
  }
}
