#ifndef _PARTICLE_CABLE_H_
#define _PARTICLE_CABLE_H_

#include "particle.hpp"
#include "particle_contact.hpp"
#include "particle_link.hpp"

class ParticleCable : public ParticleLink {
private:
  float max_length;
  float coeff_restitution;
  
public:
  ParticleCable(Particle* particles[2], float max_length, float coeff_restitution);

  ParticleContact* add_contact();
  
};

#endif
