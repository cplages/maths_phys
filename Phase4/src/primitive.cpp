#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "matrix34.hpp"
#include "primitive.hpp"

Primitive::Primitive() {
  rigidbody = new Rigidbody();
  offset = Matrix34();
}


Primitive::Primitive(Rigidbody * r0) {
  rigidbody = r0;
}

Primitive::Primitive(Rigidbody * r0, Matrix34 o) {
  rigidbody = r0;
  offset = o;
}

Rigidbody * Primitive::get_rigidbody() {
  return rigidbody;
}

Matrix34 Primitive::get_offset(){
  return offset;
}
