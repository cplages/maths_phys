#include "rigidbody.hpp"
#include "vector3D.hpp"
#include "primitive.hpp"
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
