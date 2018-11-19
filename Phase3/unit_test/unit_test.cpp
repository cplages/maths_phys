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
  Quaternion q = Quaternion(1,1,1,1);

  Matrix33 result = Matrix33(-3, 4, 0, 0, -3, 4, 4, 0, -3);
  assert(result == quaternion_to_matrix(q));
  
}

//inverse matrix 33
void inverse_matrix_33() {
  Matrix33 m1 = Matrix33(1,2,3,0,1,4,5,6,0);

  Matrix33 result = Matrix33(-24, 18, 5, 20, -15, -4, -5, 4, 1);

  assert(result == m1.inverse());
}

//inverse matrix 34

// void inverse_matrix_34() {
//   Matrix34 m1 = Matrix34(0,1,1,1,2,2,2,2,3,3,3,3);

//   Matrix34 result = Matrix34();

//   assert(result == m1.inverse());
// }

//do rotation

//quaternion *=

//quaternion * float

//update angular velocity


int main() {
  printf("test launched....1\n");
  matrix33_multiply_test();
  printf("test launched....2\n");
  matrix34_multiply_vector();
  printf("test launched....3\n");
  quaternion_to_matrix_test();
  printf("test launched....4\n");
  inverse_matrix_33();
  printf("all done! \n");
  return 0;
}

