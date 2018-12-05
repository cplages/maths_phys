#include "rigidbody.hpp"
#include "primitive.hpp"
#include "vector3D.hpp"
#include <stdio.h>
#include "box.hpp"

Box::Box(): Primitive()
{
}

Box::Box(Rigidbody * r0, float width, float height, float deepness):Primitive(r0) {
  half_size = Vector3D(width/2, height/2, deepness/2);
  calculate_vertex_coordinate();
}

Vector3D * Box::calculate_vertex_coordinate() {
  Vector3D * local_vertices = new Vector3D[8];
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
	         local_vertices[index] = Vector3D(current_x, current_y, current_z);
      }
    }
  }
  return local_vertices;
}


Vector3D Box::get_half_size() {
  return half_size;
}

//Get vertices of the box from world reference
Vector3D * Box::get_vertices() {
  Vector3D * local_vertices = calculate_vertex_coordinate();
  int vertex_number = 8;
  Vector3D * world_vertices = new Vector3D[vertex_number];

  for(int i = 0; i < vertex_number; i++){
    world_vertices[i] = local_to_world(local_vertices[i]);
  }
  return world_vertices;
}


//transform point from local reference to object then world reference.
Vector3D Box::local_to_world(Vector3D point) {
  Vector3D object_coord = get_offset() * point;
  return get_rigidbody()->local_to_world(object_coord);
}

void Box::display_vertex() {

}
