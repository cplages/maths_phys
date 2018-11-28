#ifndef _RIGIDBODY_DRAG_GENERATOR_
#define _RIGIDBODY_DRAG_GENERATOR_

#include "rigidbody_force_generator.hpp"

class RigidbodyDragGenerator : public RigidbodyForceGenerator {

private :
  float k1;
  float k2;

public :
  RigidbodyDragGenerator(float k1, float k2);
  void update_force(Rigidbody * rigidbody, float period);
};


#endif
