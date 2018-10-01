#ifndef _PARTICLE_GRAVITY_GENERATOR_
#define _PARTICLE_GRAVITY_GENERATOR_

#include "particle_force_generator.hpp"

class ParticleGravityGenerator : public ParticleForceGenerator {

private :
  Vector3D gravity;

public :
  ParticleGravityGenerator(Vector3D g0);
  void update_force(Particle * particle, float period); 
};


#endif
