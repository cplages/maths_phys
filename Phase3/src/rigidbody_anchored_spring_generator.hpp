#ifndef _RIGIDBODY_ANCHORED_SPRING_GENERATOR_
#define _RIGIDBODY_ANCHORED_SPRING_GENERATOR_

#include "rigidbody_force_generator.hpp"

class RigidbodyAnchoredSpringGenerator : public RigidbodyForceGenerator {

private :
  Vector3D anchored_point;
  float k;
  float l0;

public :
  RigidbodyAnchoredSpringGenerator(Vector3D anchored_point);
  void update_force(Rigidbody * rigidbody, float period);
};


#endif
