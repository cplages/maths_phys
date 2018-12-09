#include "vector3D.hpp"
#include "primitive.hpp"
#include "sphere.hpp"

Sphere::Sphere():Primitive() {
  radius = 0;
}

Sphere::Sphere(Rigidbody * r0, float radius0):Primitive(r0, Matrix34::identity_matrix()) {
  radius = radius0;
}

float Sphere::get_radius() {
  return radius;
}
