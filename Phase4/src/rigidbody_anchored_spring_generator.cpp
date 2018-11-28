#include "vector3D.hpp"

#include "rigidbody_anchored_spring_generator.hpp"


RigidbodyAnchoredSpringGenerator::RigidbodyAnchoredSpringGenerator(Vector3D anchored_point) {
  this->anchored_point = anchored_point;
  this->k = k;
  this->l0 = l0;
}

void  RigidbodyAnchoredSpringGenerator::update_force(Rigidbody * rigidbody, float period) {

  Vector3D dist = anchored_point - rigidbody->get_position();
  float l = dist.norm();
  Vector3D unit_dist = dist * (1 / l);

  float coef = -(this->k) * (l  - this->l0);
  Vector3D force = unit_dist * coef;

  rigidbody->add_force(force);
}
