#include "vector3D.hpp"

#include "particle_anchored_spring_generator.hpp"


ParticleAnchoredSpringGenerator::ParticleAnchoredSpringGenerator(Vector3D anchored_point) {
  this->anchored_point = anchored_point;
  this->k = k;
  this->l0 = l0;
}

void  ParticleAnchoredSpringGenerator::update_force(Particle * particle, float period) {

  Vector3D dist = anchored_point - particle->get_position();
  float l = dist.norm();
  Vector3D unit_dist = dist * (1 / l);

  float coef = -(this->k) * (l  - this->l0);
  Vector3D force = unit_dist * coef;

  particle->add_force(force);
}
