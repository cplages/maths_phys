#ifndef _RIGIDBODY_BUNGEE_GENERATOR_
#define _RIGIDBODY_BUNGEE_GENERATOR_

#include "rigidbody_force_generator.hpp"
#include "rigidbody_spring_generator.hpp"

class RigidbodyBungeeGenerator : public RigidbodySpringGenerator {

public :
  RigidbodyBungeeGenerator(Rigidbody * other_rigidbody, float k, float l0);
  void update_force(Rigidbody * rigidbody, float period);
};


#endif
