#ifndef _PARTICLE_ANCHORED_SPRING_GENERATOR_
#define _PARTICLE_ANCHORED_SPRING_GENERATOR_

#include "particle_force_generator.hpp"

class ParticleAnchoredSpringGenerator : public ParticleForceGenerator {

private :
  Vector3D anchored_point;
  float k;
  float l0;

public :
  ParticleAnchoredSpringGenerator(Vector3D anchored_point);
  void update_force(Particle * particle, float period);
};


#endif
