#include "rigidbody.hpp"
#include "primitive.hpp"
#include "vector3D.hpp"
#include "matrix34.hpp"
#include <stdio.h>
#include "box.hpp"

Box::Box(): Primitive()
{
}

Box::Box(Rigidbody * r0, float width, float height, float deepness, Matrix34 offset):Primitive(r0, offset) {
  half_size = Vector3D(width/2, height/2, deepness/2);
}



Vector3D Box::get_half_size() {
  return half_size;
}

//Get vertices of the box from world reference
Vector3D * Box::get_vertices() {
  Vector3D * local_vertices = calculate_vertex_coordinate(half_size);
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

//Check if box is in the current octree
bool Box::primitive_in_octree(Vector3D p0, Vector3D d0) {
    float distance_centers = get_rigidbody()->get_position().distance(&p0);
    float sum_diagonals = half_size.norm() + (d0/2).norm();
    return distance_centers <= sum_diagonals;
}

// Compute 8 vertices of the box with the dimension
Vector3D * calculate_vertex_coordinate(Vector3D half_size) {
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
