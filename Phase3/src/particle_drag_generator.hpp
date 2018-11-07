#ifndef _PARTICLE_DRAG_GENERATOR_
#define _PARTICLE_DRAG_GENERATOR_

#include "particle_force_generator.hpp"

class ParticleDragGenerator : public ParticleForceGenerator {

private :
  float k1;
  float k2;

public :
  ParticleDragGenerator(float k1, float k2);
  void update_force(Particle * particle, float period); 
};


#endif
