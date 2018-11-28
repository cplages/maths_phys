#ifndef _RIGIDBODY_SPRING_GENERATOR_
#define _RIGIDBODY_SPRING_GENERATOR_

#include "rigidbody_force_generator.hpp"

class RigidbodySpringGenerator : public RigidbodyForceGenerator {

protected :
  Rigidbody * other_rigidbody;
  float k;
  float l0;

public :
  RigidbodySpringGenerator(Rigidbody * other_rigidbody, float k, float l0);
  virtual void update_force(Rigidbody * rigidbody, float period);
};


#endif
