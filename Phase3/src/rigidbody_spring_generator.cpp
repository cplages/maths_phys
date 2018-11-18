#include "vector3D.hpp"

#include "rigidbody_spring_generator.hpp"



RigidbodySpringGenerator::RigidbodySpringGenerator(Rigidbody * other_rigidbody, float k, float l0){
  this->other_rigidbody = other_rigidbody;
  this->k = k;
  this->l0 = l0;
}


void  RigidbodySpringGenerator::update_force(Rigidbody * rigidbody, float period){

  Vector3D dist = rigidbody->get_position() - other_rigidbody->get_position();
  float l = dist.norm();
  Vector3D unit_dist = dist * (1 / l);

  float coef = -(this->k) * (l  - this->l0);
  Vector3D force = unit_dist * coef;

  rigidbody->add_force(force);
}
