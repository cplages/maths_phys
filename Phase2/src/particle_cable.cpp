#include <cstddef>
#include <cstdio>

#include "particle_cable.hpp"


ParticleCable::ParticleCable(Particle* particles[], float coeff_restitution, float max_length): coeff_restitution(coeff_restitution), max_length(max_length)
{
  this->particles[0] = particles[0];
  this->particles[1] = particles[1];
}

ParticleContact* ParticleCable::add_contact()
{
  if(get_length() >= max_length)
  {
    return new ParticleContact(particles[0], particles[1], coeff_restitution, 0, true); 
  }
  return NULL;
}
