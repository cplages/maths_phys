#include "particle_cable.hpp"

ParticleCable::ParticleCable(Particle* particles[], float max_length, float coeff_restitution): max_length(max_length), coeff_restitution(coeff_restitution)
{
  this->particles[0] = particles[0];
  this->particles[1] = particles[1];
}

ParticleContact* ParticleCable::add_contact()
{
  return new ParticleContact(particles[0], particles[1], coeff_restitution);
}