#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "primitive.hpp"

Primitive::Primitive() {
  rigidbody = new Rigidbody();
}

Primitive::Primitive(Rigidbody * r0) {
  rigidbody = r0;
}

Vector3D Primitive::get_position() {
  rigidbody->get_position();
}

Vector3D Primitive::get_velocity() {
  rigidbody->get_velocity();
}



