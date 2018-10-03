#ifndef _PARTICLE_CONTACT_RESOLVER_H
#define _PARTICLE_CONTACT_RESOLVER_H

#include "particle_contact.hpp"

class ParticleContactResolver {
private:
  int max_iteration;
  vector<ParticleContact *> collisions;

  
public:
  ParticleContactResolver(int max_iteration,  vector<ParticleContact *> collisions);
  void resolve_contacts();
};


#endif //_PARTICLE_CONTACT_RESOLVER_H
