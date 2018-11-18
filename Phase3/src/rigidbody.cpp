#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <float.h>

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
  this->transform_matrix = Matrix34();
  this->accum_force = Vector3D();
  this->accum_torque = Vector3D();
}

Rigidbody::Rigidbody(Vector3D p0, Vector3D r0, Vector3D v0, float m0, float ld0, float ad0, Quaternion o0, Matrix34 transform0, Matrix33 tensor0) {
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

Vector3D Rigidbody::get_position(){
  return position;
}

Vector3D Rigidbody::get_velocity(){
  return position;
}

float Rigidbody::get_inverse_mass(){
  return inverse_mass;
}

void Rigidbody::calcul_derived_data() {
  //Rotation part of the transform matrix
  Matrix33 tmp_transform = quaternion_to_matrix(orientation);
  for (int i = 0; i < tmp_transform.size; i++){
    for (int j = 0; j < tmp_transform.size; j++){
      transform_matrix.m[i][j] = tmp_transform.m[i][j];
    }
  }
  //Position part of the transform matrix
  for (int i = 0; i < transform_matrix.height - 1; i++){
    transform_matrix.m[3][i] = position.get_by_index(i);
  }

  inverse_inertia_tensor = tmp_transform * inverse_inertia_tensor * tmp_transform.inverse();

}

//modified grizzly is useless.
void Rigidbody::add_force_at_point(Vector3D force, Vector3D point) {
  point = world_to_local(point);
  add_force_at_body_point(force, point);
}

void Rigidbody::add_force_at_body_point(Vector3D force, Vector3D point) {
  add_force(force);
  add_torque(force.cross_product(&point));
}

void Rigidbody::integrate(float t) {
  //Linear acceleration
  Vector3D acceleration = this->accum_force * this->inverse_mass;
  //Angular acceleration
  Vector3D angular_acceleration = this->inverse_inertia_tensor * this->accum_torque;

  //Update velocity
  Vector3D at = acceleration * t;
  Vector3D new_v = this->velocity * pow(linear_damping, t) + at;
  this->velocity = new_v;

  //Update angular velocity (rotation)
  Vector3D angular_at = angular_acceleration * t;
  Vector3D new_ang_v = this->rotation * pow(angular_damping, t) + angular_at;
  this->rotation = new_ang_v;

  //Update position
  Vector3D vt = this->velocity * t;
  Vector3D new_p = this->position + vt;
  this->position = new_p;

  //Update orientation
  this->orientation.update_angular_velocity(this->rotation, t);

  this->calcul_derived_data();

  this->clear_accum();

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

Matrix33 Rigidbody::get_linear_transform(){
  Matrix33 linear_transform = Matrix33();
  for (int i = 0; i < linear_transform.size; i++){
    for (int j = 0; j < linear_transform.size; j++){
      linear_transform.m[i][j] = transform_matrix.m[i][j];
    }
  }
  return linear_transform;
}

//transform point from local reference to world reference.
Vector3D Rigidbody::local_to_world(Vector3D point) {
  return get_linear_transform() * point;
}

//transform point from world reference to local reference.
Vector3D Rigidbody::world_to_local(Vector3D point) {
  return (get_linear_transform().inverse()) * point;
}
