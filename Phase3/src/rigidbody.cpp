#include <cstdlib>
#include <math.h>

#include "rigidbody.hpp"



Rigidbody::Rigidbody(){
  this->position = Vector3D();
  this->rotation = Vector3D();
  this->velocity = Vector3D();
  this->inverse_mass = 0;
  this->inverse_inertia_tensor = Matrix33();
  this->linear_damping = 0;
  this->angular_damping = 0;
  this->orientation = Quaternion();
  this->transform_matrix = Matrix33();
  this->accum_force = Vector3D();
  this->accum_torque = Vector3D();
}

Rigidbody::Rigidbody(Vector3D p0, Vector3D r0, Vector3D v0, float m0, float ld0, float ad0, Quaternion o0, Matrix33 transform0, Matrix33 tensor0) {
  this->position = p0;
  this->rotation = r0;
  this->velocity = v0;
    //Checking if the mass is not null
  if (m0 == 0){
    printf("Masse nulle impossible\n");
    this->inverse_mass = FLT_MAX;
  }
  else {
    this->inverse_mass = 1 / m0;
  }
  
  this->inverse_inertia_tensor = tensor0.inverse();
  
  this->linear_damping = ld0;
  this->angular_damping = ad0;
  this->orientation = o0;
  this->transform_matrix = transform0;
  
  this->accum_force = Vector3D();
  this->accum_torque = Vector3D();
}

void Rigidbody::calcul_derived_data() {
  transform_matrix = quaternion_to_matrix(orientation);

  inverse_inertia_tensor = transform_matrix * inverse_inertia_tensor * transform_matrix.inverse();

}

//modified grizzly is useless.
void Rigidbody::add_force_at_point(Vector3D force, vector3D point) {
  point = world_to_local(point, transform_matrix);
  add_force_at_body_point(force, point);
}

void Rigidbody::add_force_at_body_point(Vector3D force, vector3D point) {
  add_force(force);
  add_torque(force.cross_product(point));
}

void Rigidbody::integrate(float t) {
  //later
}

void Rigidbody::add_force(const Vector3D &force) {
    accum_force += force;
}

void Rigidbody::add_torque(const Vector3D &torque) {
  accum_torque += torque;
}

void Rigidbody::clear_accum() {
  accum_force = Vector3D();
  accum_force = Vector3D();
}
