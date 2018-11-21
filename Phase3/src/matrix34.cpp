#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix33.hpp"
#include "matrix34.hpp"
#include "vector3D.hpp"
#include "quaternion.hpp"

//constructors
Matrix34::Matrix34(){
    for (int i = 0; i<height; i++){
      for (int j = 0; j<width; j++){
        m[i][j] = 0;
      }
    }
}

Matrix34::Matrix34(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l){
    m[0][0] = a;
    m[0][1] = b;
    m[0][2] = c;
    m[0][3] = d;
    m[1][0] = e;
    m[1][1] = f;
    m[1][2] = g;
    m[1][3] = h;
    m[2][0] = i;
    m[2][1] = j;
    m[2][2] = k;
    m[2][3] = l;
}


Matrix34 Matrix34::inverse(){
  float d = (m[2][0] * m[1][1] * m[0][2])
    + (m[1][0] * m[2][1] * m[0][2])
    + (m[2][0] * m[0][1] * m[1][2])
    - (m[0][0] * m[2][1] * m[1][2])
    - (m[1][0] * m[0][1] * m[2][2])
    + (m[0][0] * m[1][1] * m[2][2]);

  if (d != 0){

   Matrix34 inverse_m = Matrix34( (m[1][1]*m[2][2] - m[1][2]*m[2][1]),
   (m[0][2]*m[2][1] - m[0][1]*m[2][2]),
   (m[0][1]*m[1][2] - m[0][2]*m[1][1]),
   (m[2][1]*m[1][2]*m[0][3] - m[1][1]*m[2][2]*m[0][3] - m[2][1]*m[0][2]*m[1][3] + m[0][1]*m[2][2]*m[1][3] + m[1][1]*m[0][2]*m[2][3] - m[0][1]*m[1][2]*m[2][3]),
   (m[1][2]*m[2][0] - m[1][0]*m[2][2]),
   (m[0][0]*m[2][2] - m[0][2]*m[2][0]),
   (m[0][2]*m[1][0] - m[0][0]*m[1][2]),
   (- m[2][0]*m[1][2]*m[0][3] + m[1][0]*m[2][2]*m[0][3] + m[2][0]*m[0][2]*m[1][3] - m[0][0]*m[2][2]*m[1][3] - m[1][0]*m[0][2]*m[2][3] + m[0][0]*m[1][2]*m[2][3]),
   (m[1][0]*m[2][1] - m[1][1]*m[2][0]),
   (m[0][1]*m[2][0] - m[0][0]*m[2][1]),
   (m[0][0]*m[1][1] - m[0][1]*m[1][0]),
   (m[2][1]*m[1][1]*m[0][3] - m[1][1]*m[2][1]*m[0][3] - m[2][1]*m[0][1]*m[1][3] + m[0][1]*m[2][1]*m[1][3] + m[1][1]*m[0][1]*m[2][3] - m[0][1]*m[1][1]*m[2][3]) );

   return inverse_m * (1/d);
  }
  return Matrix34();
}

Matrix34 Matrix34::identity_matrix() {
  Matrix34 identity = Matrix34();
  for(int i = 0; i < height; ++i) {
    identity.m[i][i] = 1;
  }
  return identity;
}

Matrix33 Matrix34::get_linear_transform(){
  Matrix33 linear_transform = Matrix33();
  for (int i = 0; i < linear_transform.size; i++){
    for (int j = 0; j < linear_transform.size; j++){
      linear_transform.m[i][j] = this->m[i][j];
    }
  }
  return linear_transform;
}

//operators
Matrix34& Matrix34::operator = (Matrix34 const& m){
  for (int i = 0; i<height; i++){
    for (int j = 0; j<width; j++){
      this->m[i][j] = m.m[i][j];
    }
  }
  return *this;
}

bool Matrix34::operator ==(Matrix34 const& v) {
  bool is_equal = true;
  for (int i = 0; i<height; i++){
    for (int j = 0; j<width; j++){
      if(this->m[i][j] != v.m[i][j]) {
	is_equal = false;
      }
    }
  }
  return is_equal;
}


//binary operators outside the class
Matrix34 operator * (Matrix34 const& m, float const& f){
  Matrix34 copy = m;
  for (int i = 0; i<m.height; i++){
    for (int j = 0; j<m.width; j++){
      copy.m[i][j] *= f;
    }
  }
  return copy;
}

Vector3D operator * (Matrix34 const& m, Vector3D const& v){
  Vector3D result = Vector3D();
  for (int i = 0; i<m.height; i++){
    for (int j = 0; j<m.width-1; j++){
      result.set_by_index(i, result.get_by_index(i) + m.m[i][j] * v.get_by_index(j));
    }
    result.set_by_index(i, result.get_by_index(i) + m.m[i][m.width - 1]);
  }
  return result;
}

Matrix34 operator * (Matrix34 const& m1, Matrix34 const& m2){
  Matrix34 copy = Matrix34();
  for (int i = 0; i<copy.height; i++){
    for (int j = 0; j<copy.width-1; j++){
      for (int k = 0; k<copy.height; k++){
        copy.m[i][j] += m1.m[i][k] * m2.m[k][j];
      }
    }
    copy.m[i][copy.width-1] = m1.m[i][m1.width-1] + m2.m[i][m2.width-1];
  }
  return copy;
}

Matrix34 set_orientation(Quaternion q){
  Matrix34 result = Matrix34( (1 - (2 * pow(q.coord[2],2) + 2 * pow(q.coord[3],2))),
  ((2 * q.coord[1] * q.coord[2]) + (2 * q.coord[3] * q.coord[0])),
  ((2 * q.coord[1] * q.coord[3]) - (2 * q.coord[2] * q.coord[0])),
  q.coord[1],
  ((2 * q.coord[1] * q.coord[2]) - (2 * q.coord[3] * q.coord[0])),
  (1 - (2 * pow(q.coord[1],2) + 2 * pow(q.coord[3],2))),
  ((2 * q.coord[2] * q.coord[3]) + (2 * q.coord[1] * q.coord[0])),
  q.coord[2],
  ((2 * q.coord[1] * q.coord[3]) + (2 * q.coord[2] * q.coord[0])),
  ((2 * q.coord[2] * q.coord[3]) - (2 * q.coord[1] * q.coord[0])),
  (1 - (2 * pow(q.coord[1],2) + 2 * pow(q.coord[2],2))),
  q.coord[3]);

  return result;
}


Vector3D apply_transformation(Matrix34 transform, Vector3D v){
  return transform.get_linear_transform() * v;
}

Vector3D apply_inverse_transformation(Matrix34 transform, Vector3D v){
  return transform.get_linear_transform().inverse() * v;
}


