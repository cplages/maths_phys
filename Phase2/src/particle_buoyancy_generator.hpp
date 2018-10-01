#ifndef _PARTICLE_BUOYANCY_GENERATOR_
#define _PARTICLE_BUOYANCY_GENERATOR_

#include "particle_force_generator.hpp"

class ParticleBuoyancyGenerator : public ParticleForceGenerator {

private :
  float max_deepness;
  float object_volume;
  float water_height;
  float density;

public :
  ParticleBuoyancyGenerator(float max_deepness, float object_volume, float water_height, float density);
  void update_force(Particle * particle, float period); 
};


#endif
