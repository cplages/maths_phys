#ifndef _PARTICLE_ROD_H_
#define _PARTICLE_ROD_H_

#include "particle.hpp"
#include "particle_contact.hpp"
#include "particle_link.hpp"

/* Identical to a ParticleCable with 0 for the restitution coefficient */
class ParticleRod : public ParticleLink {
private:
  float max_length;

public:
  ParticleRod(Particle * particles[2], float max_length);

  ParticleContact* add_contact();

};

#endif
