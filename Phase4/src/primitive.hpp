#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"


class Primitive {

private:
  Rigidbody * rigidbody;

public:

  Primitive();

  Primitive(Rigidbody * r0);

  Vector3D get_position();

  Vector3D get_velocity();

};


#endif //PRIMITVE_H
