#ifndef _MATRIX_33_
#define _MATRIX_33_

#include "vector3D.hpp"

/*
 Class representing 3*3 Matrix
 */

class Matrix33{

public:
  int size;
  float m[3][3];

  Matrix33();
  Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i);

  Matrix33 inverse();
  Matrix33 transpose();




  //operators
  Matrix33& operator = (Matrix33 const& m);

};

//binary operators outside the class
Matrix33 operator * (Matrix33 const& m, float const& f);
Vector3D operator * (Matrix33 const& m, Vector3D const& v);
Matrix33 operator * (Matrix33 const& m1, Matrix33 const& m2);

#endif
