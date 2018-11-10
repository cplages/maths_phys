#ifndef _MATRIX_34_
#define _MATRIX_34_

#include "vector3D.hpp"
#include "quaternion.hpp"

/*
 Class representing 3*4 Matrix
 */

class Matrix34{

public:
  int width;
  int height;
  float m[3][4];

  Matrix34();
  Matrix34(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l);

  Matrix34 inverse();

  //operators
  Matrix34& operator = (Matrix34 const& m);

};

//binary operators outside the class
Matrix34 operator * (Matrix34 const& m, float const& f);
Vector3D operator * (Matrix34 const& m, Vector3D const& v);
Matrix34 operator * (Matrix34 const& m1, Matrix34 const& m2);

Matrix34 set_orientation(Quaternion q);

Vector3D apply_transformation(Matrix34 transform, Vector3D v);
Vector3D apply_inverse_transformation(Matrix34 transform, Vector3D v);


#endif
