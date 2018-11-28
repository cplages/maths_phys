#ifndef _MATRIX_33_
#define _MATRIX_33_

#include "vector3D.hpp"
#include "quaternion.hpp"

/*
 Class representing 3*3 Matrix
 */

class Matrix33{

public:
  static const int size = 3 ;
  float m[3][3];

  Matrix33();
  Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i);

  Matrix33 inverse();
  Matrix33 transpose();

  static Matrix33 identity_matrix();

  void display() const;
  
  //operators
  Matrix33& operator = (Matrix33 const& m);
  bool operator ==(Matrix33 const& v);

};

Matrix33 quaternion_to_matrix(Quaternion q);

//binary operators outside the class
Matrix33 operator * (Matrix33 const& m, float const& f);
Vector3D operator * (Matrix33 const& m, Vector3D const& v);
Matrix33 operator * (Matrix33 const& m1, Matrix33 const& m2);

#endif
