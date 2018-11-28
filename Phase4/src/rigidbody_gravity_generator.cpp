#include <stdio.h>
#include <stdlib.h>
#include "rigidbody_gravity_generator.hpp"


RigidbodyGravityGenerator::RigidbodyGravityGenerator(Vector3D g0){
  this->gravity = g0;
}

void RigidbodyGravityGenerator::update_force(Rigidbody * rigidbody, float period){

  // The verification of the mass not null already done in the rigidbody constructor
  // No need to do it again here
  float mass = 1 / rigidbody->get_inverse_mass();
  rigidbody->add_force(this->gravity * mass);
}
