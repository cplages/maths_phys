#ifndef _RIGIDBODY_BUOYANCY_GENERATOR_
#define _RIGIDBODY_BUOYANCY_GENERATOR_

#include "rigidbody_force_generator.hpp"

class RigidbodyBuoyancyGenerator : public RigidbodyForceGenerator {

private :
  float max_deepness;
  float object_volume;
  float water_height;
  float density;

public :
  RigidbodyBuoyancyGenerator(float max_deepness, float object_volume, float water_height, float density);
  void update_force(Rigidbody * rigidbody, float period);
};


#endif
