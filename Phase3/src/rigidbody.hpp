#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

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
  
  void calcul_derived_data();

  void add_force_at_point(Vector3D force, vector3D point);
  void add_force_at_body_point(Vector3D force, vector3D point);

  void integrate(float t);

  void add_force(const Vector3D &force);
  void add_torque(const Vector3D &torque);
  void clear_accum();
  
  
};


#endif //_RIGIDBODY_H_
