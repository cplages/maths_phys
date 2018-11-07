#ifndef _PARTICLE_CONTACT_GENERATOR_H_
#define _PARTICLE_CONTACT_GENERATOR_H_

#include "particle_contact.hpp"

class ParticleContactGenerator {
public:
  virtual ParticleContact* add_contact() = 0;
};



#endif
