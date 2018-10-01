#include "vector3D.hpp"

#include "particle_spring_generator.hpp"



ParticleSpringGenerator::ParticleSpringGenerator(Particle other_particle, float k, float l0){
  this->other_particle = other_particle;
  this->k = k;
  this->l0 = l0;
}


void  ParticleSpringGenerator::update_force(Particle * particle, float period){

  Vector3D dist = other_particle.get_position() - particle->get_position();
  float l = dist.norm();
  Vector3D unit_dist = dist * (1 / l);

  float coef = -(this->k) * (l  - this->l0);
  Vector3D force = unit_dist * coef;

  particle->add_force(force);
}
