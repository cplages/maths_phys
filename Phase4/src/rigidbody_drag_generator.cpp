#include <math.h>
#include "rigidbody_drag_generator.hpp"

RigidbodyDragGenerator::RigidbodyDragGenerator(float k1, float k2){
  this->k1 = k1;
  this->k2 = k2;
}

void RigidbodyDragGenerator::update_force(Rigidbody * rigidbody, float period){

  Vector3D velocity = rigidbody->get_velocity();
  float velocity_norm = velocity.norm();
  if (velocity_norm != 0){
    Vector3D unit_velocity = velocity * (1 / velocity_norm);

    Vector3D force = (unit_velocity * ( k1 * velocity_norm + k2 * pow(velocity_norm, 2))) * -1;

    rigidbody->add_force(force);
  }

}
