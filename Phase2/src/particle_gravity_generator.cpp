#include "particle_gravity_generator.hpp"

ParticleGravityGenerator::ParticleGravityGenerator(Vector3D g0){
  this->gravity = g0;
}

void ParticleGravityGenerator::update_force(Particle * particle, float period){

  // The verification of the mass not null already done in the particle constructor
  // No need to do it again here
  float mass = 1 / particle->get_inverse_mass();

  particle->add_force(this->gravity * mass);
}
