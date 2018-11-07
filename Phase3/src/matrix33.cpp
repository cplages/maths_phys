#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix33.hpp"
#include "vector3D.hpp"

//constructors
Matrix33::Matrix33(){
  size = 3;
    for (int i = 0; i<size; i++){
      for (int j = 0; j<size; j++){
        m[i][j] = 0;
      }
    }
}

Matrix33::Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i){
    size = 3;
    m[0][0] = a;
    m[0][1] = b;
    m[0][2] = c;
    m[1][0] = d;
    m[1][1] = e;
    m[1][2] = f;
    m[2][0] = g;
    m[2][1] = h;
    m[2][2] = i;
}


Matrix33 Matrix33::inverse(){
  float d = (m[0][0] * m[1][1] * m[2][2])
    + (m[1][0] * m[2][1] * m[0][2])
    + (m[2][0] * m[0][1] * m[1][2])
    - (m[0][0] * m[2][1] * m[1][2])
    - (m[2][0] * m[1][1] * m[0][2])
    - (m[1][0] * m[0][1] * m[2][2]);

  if (d != 0){

   Matrix33 inverse_m = Matrix33( (m[1][1]*m[2][2] - m[1][2]*m[2][1]),
   (m[0][2]*m[2][1] - m[0][1]*m[2][2]),
   (m[0][1]*m[1][2] - m[0][2]*m[1][1]),
   (m[1][2]*m[2][0] - m[1][0]*m[2][2]),
   (m[0][0]*m[2][2] - m[0][2]*m[2][0]),
   (m[0][2]*m[1][0] - m[0][0]*m[1][2]),
   (m[1][0]*m[2][1] - m[1][1]*m[2][0]),
   (m[0][1]*m[2][0] - m[0][0]*m[2][1]),
   (m[0][0]*m[1][1] - m[0][1]*m[1][0]));

   return inverse_m * (1/d);
  }
  return Matrix33();
}



Matrix33 Matrix33::transpose(){
  Matrix33 transpose_m = *this;
  for (int i = 0; i<size-1; i++){
    for (int j = i+1; j< size; j++){
      float tmp = transpose_m.m[i][j];
      transpose_m.m[i][j] = transpose_m.m[j][i];
      transpose_m.m[j][i] = tmp;
    }
  }
  return transpose_m;
}


//operators
Matrix33& Matrix33::operator = (Matrix33 const& m){
  for (int i = 0; i<size; i++){
    for (int j = 0; j<size; j++){
      this->m[i][j] = m.m[i][j];
    }
  }
  this->size = m.size;
  return *this;
}

//binary operators outside the class
Matrix33 operator * (Matrix33 const& m, float const& f){
  Matrix33 copy = m;
  for (int i = 0; i<m.size; i++){
    for (int j = 0; j<m.size; j++){
      copy.m[i][j] *= f;
    }
  }
  return copy;
}

Vector3D operator * (Matrix33 const& m, Vector3D const& v){
  Vector3D result = Vector3D();
  for (int i = 0; i<m.size; i++){
    for (int j = 0; j<m.size; j++){
      result.set_by_index(i, result.get_by_index(i) + m.m[i][j] * v.get_by_index(i));
    }
  }
  return result;
}

Matrix33 operator * (Matrix33 const& m1, Matrix33 const& m2){
  Matrix33 copy = Matrix33();
  for (int i = 0; i<copy.size; i++){
    for (int j = 0; j<copy.size; j++){
      for (int k = 0; k<copy.size; k++){
        copy.m[i][j] += m1.m[i][k] * m2.m[j][k]; //inchallah
      }
    }
  }
  return copy;
}
