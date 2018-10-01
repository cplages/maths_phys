#include "vector3D.hpp"

#include "particle_bungee_generator.hpp"



ParticleBungeeGenerator::ParticleBungeeGenerator(Particle other_particle, float k, float l0):
ParticleSpringGenerator(other_particle, k, l0){}



void ParticleBungeeGenerator::update_force(Particle * particle, float period){

  Vector3D dist = other_particle.get_position() - particle->get_position();
  float l = dist.norm();

  Vector3D force;
  // compression don't produce force
  if (l <= this->l0){
    force = Vector3D();
  }
  else {
    Vector3D unit_dist = dist * (1 / l);

    float coef = -(this->k) * (l  - this->l0);
    Vector3D force = unit_dist * coef;
  }

  particle->add_force(force);
}
