#include "particule_gravity_generator.hpp"

ParticuleGravityGenerator::ParticuleGravityGenerator(Vector3D g0){
  this->gravity = g0;
}

void ParticuleGravityGenerator::update_force(Particule * particule, float period){

  // The verification of the mass not null already done in the particule constructor
  // No need to do it again here
  float mass = 1 / particule->get_inverse_mass();

  particule->add_force(this->gravity * mass);
}
