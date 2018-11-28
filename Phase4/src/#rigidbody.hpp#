#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "vector3D.hpp"
#include "matrix33.hpp"
#include "matrix34.hpp"
#include "quaternion.hpp"

class Rigidbody {
private:
  Vector3D position;
  Vector3D rotation;
  Vector3D velocity;
  float inverse_mass;
  Matrix33 inverse_inertia_tensor;
  float linear_damping;
  float angular_damping;
  Quaternion orientation;
  Matrix34 transform_matrix;

  Vector3D accum_force;
  Vector3D accum_torque;


public:

  Rigidbody();
  Rigidbody(Vector3D p0, Vector3D r0, Vector3D v0, float m0, float ld0, float ad0, Quaternion o0, Matrix34 transform0, Matrix33 tensor0);

  Vector3D get_position();
  Vector3D get_velocity();
  float get_inverse_mass();

  void calcul_derived_data();

  void add_force_at_point(Vector3D force, Vector3D point);
  void add_force_at_body_point(Vector3D force, Vector3D point);

  void integrate(float t);

  void add_force(const Vector3D &force);
  void add_torque(const Vector3D &torque);
  void clear_accum();

  Vector3D local_to_world(Vector3D point);
  Vector3D world_to_local(Vector3D point);

};



#endif //_RIGIDBODY_H_
