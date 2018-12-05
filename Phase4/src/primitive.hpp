#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "matrix34.hpp"

class Primitive {

private:
  Rigidbody * rigidbody;
  Matrix34 offset;


public:

  Primitive();

  Primitive(Rigidbody * r0);

  Primitive(Rigidbody * r0, Matrix34 o);

  Rigidbody * get_rigidbody();

  Matrix34 get_offset();

};


#endif //PRIMITVE_H
