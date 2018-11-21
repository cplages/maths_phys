#include "vector3D.hpp"

#include "rigidbody_bungee_generator.hpp"



RigidbodyBungeeGenerator::RigidbodyBungeeGenerator(Rigidbody * other_rigidbody, float k, float l0):
RigidbodySpringGenerator(other_rigidbody, k, l0){}



void RigidbodyBungeeGenerator::update_force(Rigidbody * rigidbody, float period){

  Vector3D dist = other_rigidbody->get_position() - rigidbody->get_position();
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

  rigidbody->add_force_at_point(force,rigidbody->get_position());
}
