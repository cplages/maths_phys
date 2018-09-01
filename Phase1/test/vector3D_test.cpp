#include <iostream>
#include <assert.h>

#include "../src/vector3D.hpp"

using namespace std;

void equal_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(1.0f, 1.0f, 4.0f);
  Vector3D w = Vector3D(1.0f, 1.0f, 1.0f);

  assert( (u == v) == false);
  assert( (w == u) == true);
}

void add_test(){
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(2.0f, 3.0f, 4.0f);
  Vector3D result = Vector3D(3.0f, 4.0f, 5.0f);
  
  assert(u.add(&v) == result);
  assert(u.add(&v) != u);
}

void mult_scal_test(){
  float k = 3.0f;
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(2.0f, 3.0f, 4.0f);
  Vector3D result_u = Vector3D(3.0f, 3.0f, 3.0f);
  Vector3D result_v = Vector3D(6.0f, 9.0f, 12.0f);
  
  assert(u.mult_scal(k) == result_u);
  assert(v.mult_scal(k) == result_v);
}

void composant_product_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(2.0f, 3.0f, 4.0f);
  Vector3D result = Vector3D(2.0f, 3.0f, 4.0f);

  assert(u.composant_product(&v) == result);
}

void dot_product_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(2.0f, 3.0f, 4.0f);
  float result = 9;

  assert(u.dot_product(&v) == result);
}

void cross_product_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(2.0f, 3.0f, 4.0f);
  Vector3D result = Vector3D(1, -2, 1);

  assert(u.cross_product(&v) == result);
}

void norm_test() {
  Vector3D u = Vector3D(2.0f, 0.0f, 0.0f);
  float result = 2;

  assert(u.norm() == result);  
}

void proj_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(0.0f, 2.0f, 2.0f);
  Vector3D result = Vector3D(0.0f, 1.0f, 1.0f);
  assert(u.proj(&v) == result);
}

void distance_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(0.0f, 1.0f, 1.0f);
  assert(u.distance(&v) == 1);
}

void triple_product_test() {
  Vector3D u = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D v = Vector3D(1.0f, 1.0f, 1.0f);
  Vector3D w = Vector3D(2.0f, 3.0f, 4.0f);

  float result = 0;

  assert(u.triple_product(&v, &w) == result);
}

int main() {
  equal_test();
  add_test();
  mult_scal_test();
  composant_product_test();
  dot_product_test();
  cross_product_test();
  norm_test();
  proj_test();
  distance_test();
  triple_product_test();
  printf("done!\n");
}
