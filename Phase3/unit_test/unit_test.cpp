#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../src/matrix33.hpp"
#include "../src/matrix34.hpp"
#include "../src/quaternion.hpp"

//multiply matrix 33
void matrix33_multiply_test() {
  Matrix33 m1 = Matrix33(1,2,3,4,5,6,7,8,9);
  Matrix33 m2 = Matrix33(1,2,3,4,5,6,7,8,9);

  Matrix33 result = Matrix33(30, 36, 42, 66, 81, 96, 102, 126, 150);
  assert(result == m1 * m2);
}


//multiply vector matrix 34
void matrix34_multiply_vector() {
  Matrix34 m1 = Matrix34(1,2,3,1,4,5,6,1,7,8,9,1);
  Vector3D v1 = Vector3D(1,2,3);

  Vector3D result = Vector3D(7, 31, 73);
  assert(result == m1 * v1);
}

//quaternion_to_matrix
void quaternion_to_matrix_test() {
  Quaternion q = Quaternion(0.5,0.5,0.5,0.5);

  Matrix33 result = Matrix33(0,0,1,1,0,0,0,1,0);
  assert(result == quaternion_to_matrix(q));

}

//inverse matrix 33
void inverse_matrix_33() {
  Matrix33 m1 = Matrix33(1,2,3,0,1,4,5,6,0);

  Matrix33 result = Matrix33(-24, 18, 5, 20, -15, -4, -5, 4, 1);

  assert(result == m1.inverse());
}

//inverse matrix 34

//void inverse_matrix_34() {
//   Matrix34 m1 = Matrix34(0,1,1,1,2,2,2,2,3,3,3,3);

//   Matrix34 result = Matrix34();

//   assert(result == m1.inverse());
// }

//do rotation (quaternion multiply)
void quaternion_multiply(){
  Quaternion q1 = Quaternion(1,2,3,4);
  Quaternion q2 = Quaternion(1,2,3,4);

  Quaternion result = Quaternion(-28,4,6,8);

  q1 *= q2;

  assert(q1 == result);
}

//quaternion * float
void quaternion_float_multiply(){
  Quaternion q1 = Quaternion(1,2,3,4);
  float f = 2;

  Quaternion result = Quaternion(2,4,6,8);
  Quaternion q2 = q1 * f;

  assert(q2 == result);
}

//quaternion +
void quaternion_addition(){
  Quaternion q1 = Quaternion(1,2,3,4);
  Quaternion q2 = Quaternion(1,2,3,4);

  Quaternion result = Quaternion(2,4,6,8);

  Quaternion q3 = q1 + q2;
  q1 += q2;

  assert(q1 == result);
  assert(q3 == result);
}

int main() {
  printf("test launched....1\n");
  matrix33_multiply_test();
  printf("test launched....2\n");
  matrix34_multiply_vector();
  printf("test launched....3\n");
  quaternion_to_matrix_test();
  printf("test launched....4\n");
  inverse_matrix_33();
  printf("test launched....5\n");
  quaternion_multiply();
  printf("test launched....6\n");
  quaternion_float_multiply();
  printf("test launched....7\n");
  quaternion_addition();
  printf("all done! \n");
  return 0;
}
