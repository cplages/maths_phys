#ifndef _RIGIDBODY_FORCE_GENERATOR_
#define _RIGIDBODY_FORCE_GENERATOR_

#include "rigidbody.hpp"

class RigidbodyForceGenerator {
public:
  virtual void update_force(Rigidbody * rigidbody, float period) = 0;
};

#endif
