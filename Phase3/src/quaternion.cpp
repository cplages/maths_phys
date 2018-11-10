#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "quaternion.hpp"

#include "vector3D.hpp"


Quaternion::Quaternion(){
  size = 4;
  for (int i = 0; i < size; i++){
    coord[i] = 0;
  }
}
Quaternion::Quaternion(float r, float i, float j, float k){
  size = 4;
  coord[0] = r;
  coord[1] = i;
  coord[2] = j;
  coord[3] = k;
}

void Quaternion::normalize(){
  float d = 0;
  for (int i = 0; i <size; i++){
    d += pow(coord[i],2);
  }

  if (d == 0){
    coord[0] = 1;
    for (int i = 1; i <size; i++){
      coord[i] = 0;
    }
  }
  else {
    d = 1 / sqrt(d);
    for (int i = 0; i <size; i++){
      coord[i] *= d;
    }
  }
}

Quaternion& Quaternion::operator += (Quaternion const& q){
  for (int i = 0; i < size; i++){
    coord[i] += q.coord[i];
  }
  return *this;
}

Quaternion& Quaternion::operator *= (Quaternion const& q){
  for (int i = 0; i < size; i++){
    coord[i] *= q.coord[i];
  }
  return *this;
}

void Quaternion::do_rotation(Vector3D v){
  Quaternion q = Quaternion(0, v.get_x(), v.get_y(), v.get_z());
  *this *= q;
}

void Quaternion::update_angular_velocity(Vector3D v, float interval){
  Quaternion w = Quaternion();
  w.do_rotation(v);
  w *= (*this)*(interval/2);
  *this += w;
}

Quaternion operator + (Quaternion const& q1, Quaternion const& q2){
  Quaternion q = Quaternion();
  for (int i = 0; i < q.size; i++){
    q.coord[i] = q1.coord[i] + q2.coord[i];
  }
  return q;
}

Quaternion operator * (Quaternion const& q, float f){
  Quaternion result = Quaternion();
  for (int i = 0; i < result.size; i++){
    result.coord[i] = q.coord[i] * f;
  }
  return result;
}
