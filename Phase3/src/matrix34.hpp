#ifndef _MATRIX_34_
#define _MATRIX_34_

#include "vector3D.hpp"
#include "matrix33.hpp"
#include "quaternion.hpp"

/*
 Class representing 3*4 Matrix
 */

class Matrix34{

public:
  static const int height = 3;
  static const int width = 4;
  float m[3][4];

  Matrix34();
  Matrix34(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l);

  Matrix34 inverse();
  static Matrix34 identity_matrix();

  Matrix33 get_linear_transform();

  //operators
  Matrix34& operator = (Matrix34 const& m);
  bool operator ==(Matrix34 const& v);
};

//binary operators outside the class
Matrix34 operator * (Matrix34 const& m, float const& f);
Vector3D operator * (Matrix34 const& m, Vector3D const& v);
Matrix34 operator * (Matrix34 const& m1, Matrix34 const& m2);

Matrix34 set_orientation(Quaternion q);

Vector3D apply_transformation(Matrix34 transform, Vector3D v);
Vector3D apply_inverse_transformation(Matrix34 transform, Vector3D v);


#endif
