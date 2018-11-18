#ifndef _RIGIDBODY_GRAVITY_GENERATOR_
#define _RIGIDBODY_GRAVITY_GENERATOR_

#include "rigidbody.hpp"

#include "rigidbody_force_generator.hpp"

class RigidbodyGravityGenerator : public RigidbodyForceGenerator {

private :
  Vector3D gravity;

public :
  RigidbodyGravityGenerator(Vector3D g0);
  void update_force(Rigidbody * rigidbody, float period);
};


#endif
