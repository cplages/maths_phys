#ifndef _PARTICLE_FORCE_GENERATOR_
#define _PARTICLE_FORCE_GENERATOR_

#include "particle.hpp"

class ParticleForceGenerator {
public:
  virtual void update_force(Particle * particle, float period) = 0;
};

#endif
