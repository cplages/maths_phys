#include "rigidbody.hpp"
#include "vector3D.hpp"
#include "primitive.hpp"
#include "box.hpp"
#include "plane.hpp"
#include <stdio.h>

Plane::Plane():Primitive() {
}

Plane::Plane(Vector3D n, float o):Primitive(NULL) {
  normal = n;
  offset = o;
}


Vector3D Plane::get_normal(){
  return normal;
}

float Plane::get_offset(){
  return offset;
}


float Plane::get_distance_from_point(Vector3D point){
  return normal.dot_product(&point) + offset;
}

//Check if plane is in the currenc octree
bool Plane::primitive_in_octree(Vector3D p0, Vector3D d0){
      Vector3D * octree_vertices = calculate_vertex_coordinate(d0/2);
      for (int i = 0; i<8; i++){
          //check box vertex below plane
          float distance = get_distance_from_point(p0 + octree_vertices[i]);
          if (distance <= 0){
              return true;
          }
      }
      return false;
}
