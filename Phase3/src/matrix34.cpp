#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix34.hpp"
#include "vector3D.hpp"
#include "quaternion.hpp"

//constructors
Matrix34::Matrix34(){
  height = 3;
  width = 4;
    for (int i = 0; i<height; i++){
      for (int j = 0; j<width; j++){
        m[i][j] = 0;
      }
    }
}

Matrix34::Matrix34(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l){
    height = 3;
    width = 4;
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


//operators
Matrix34& Matrix34::operator = (Matrix34 const& m){
  for (int i = 0; i<height; i++){
    for (int j = 0; j<width; j++){
      this->m[i][j] = m.m[i][j];
    }
  }
  this->width = m.width;
  this->height = m.height;
  return *this;
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
    //ignore the translation part (to not modify the vector)
    for (int j = 0; j<m.width-1; j++){
      result.set_by_index(i, result.get_by_index(i) + m.m[i][j] * v.get_by_index(i));
    }
  }
  return result;
}

Matrix34 operator * (Matrix34 const& m1, Matrix34 const& m2){
  Matrix34 copy = Matrix34();
  for (int i = 0; i<copy.height; i++){
    for (int j = 0; j<copy.width-1; j++){
      for (int k = 0; k<copy.height; k++){
        copy.m[i][j] += m1.m[i][k] * m2.m[k][j]; //inchallah
      }
    }
    copy.m[i][copy.width-1] = m2.m[i][m2.width-1]; //inchallah we believe in the Grizzly
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
  q.coord[1]);

  return result;
}
