#ifndef _PARTICULE_BUOYANCY_GENERATOR_
#define _PARTICULE_BUOYANCY_GENERATOR_

#include "particule_force_generator.hpp"

class ParticuleBuoyancyGenerator : public ParticuleForceGenerator {

private :
  float max_deepness;
  float object_volume;
  float water_height;
  float density;

public :
  ParticuleBuoyancyGenerator(float max_deepness, float object_volume, float water_height, float density);
  void update_force(Particule * particule, float period); 
};


#endif
