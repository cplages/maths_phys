#ifndef _PARTICLE_LINK_H_
#define _PARTICLE_LINK_H_

#include "particle.hpp"
#include "particle_contact.hpp"
#include "particle_contact_generator.hpp"

class ParticleLink : public ParticleContactGenerator {
protected:
  ParticleLink();
  Particle* particles[2];
  
public:
  float get_length();
};


#endif
