#ifndef _PARTICLE_SPRING_GENERATOR_
#define _PARTICLE_SPRING_GENERATOR_

#include "particle_force_generator.hpp"

class ParticleSpringGenerator : public ParticleForceGenerator {

protected :
  Particle other_particle;
  float k;
  float l0;

public :
  ParticleSpringGenerator(Particle other_particle, float k, float l0);
  virtual void update_force(Particle * particle, float period);
};


#endif
