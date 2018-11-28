#ifndef _PARTICLE_CONTACT_RESOLVER_H
#define _PARTICLE_CONTACT_RESOLVER_H
#include <vector>

#include "particle_contact.hpp"


class ParticleContactResolver {
private:
  int max_iteration;
  std::vector<ParticleContact *> collisions;

  friend class ParticleContact;
  
public:
  ParticleContactResolver(std::vector<ParticleContact *> collisions);
  void resolve_contacts();
};


#endif //_PARTICLE_CONTACT_RESOLVER_H
