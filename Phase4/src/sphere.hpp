#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "rigidbody.hpp"
#include "primitive.hpp"

class Sphere : public Primitive {
private:
  float radius;

public:
  Sphere();
  Sphere(Rigidbody * r0, float radius0);

  float get_radius();
  
};


#endif //SPHERE_H
