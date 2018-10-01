#include <math.h>
#include "particle_drag_generator.hpp"

ParticleDragGenerator::ParticleDragGenerator(float k1, float k2){
  this->k1 = k1;
  this->k2 = k2;
}

void ParticleDragGenerator::update_force(Particle * particle, float period){

  Vector3D velocity = particle->get_velocity();
  float velocity_norm = velocity.norm();
  if (velocity_norm != 0){
    Vector3D unit_velocity = velocity * (1 / velocity_norm);

    Vector3D force = (unit_velocity * ( k1 * velocity_norm + k2 * pow(velocity_norm, 2))) * -1;

    particle->add_force(force);
  }

}
