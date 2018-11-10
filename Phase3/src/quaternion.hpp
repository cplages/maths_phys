#ifndef _QUATERNION_H
#define _QUATERNION_H

#include "vector3D.hpp"

class Quaternion {

public:
  int size;
  float coord[4];

  Quaternion();
  Quaternion(float r, float i, float j, float k);

  void normalize();

  Quaternion& operator += (Quaternion const& q);
  Quaternion& operator *= (Quaternion const& q);

  void do_rotation(Vector3D v);
  void update_angular_velocity(Vector3D v, float interval);
};

Quaternion operator + (Quaternion const& q1, Quaternion const& q2);
Quaternion operator * (Quaternion const& q, float f);

#endif
