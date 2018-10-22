#include "particle_rod.hpp"

ParticleRod::ParticleRod(Particle* particles[], float max_length): max_length(max_length)
{
  this->particles[0] = particles[0];
  this->particles[1] = particles[1];
}

ParticleContact* ParticleRod::add_contact()
{
    return new ParticleContact(particles[0], particles[1], 0, 0);
}
