#ifndef _PARTICLE_BUNGEE_GENERATOR_
#define _PARTICLE_BUNGEE_GENERATOR_

#include "particle_force_generator.hpp"
#include "particle_spring_generator.hpp"

class ParticleBungeeGenerator : public ParticleSpringGenerator {

public :
  ParticleBungeeGenerator(Particle other_particle, float k, float l0);
  void update_force(Particle * particle, float period);
};


#endif
