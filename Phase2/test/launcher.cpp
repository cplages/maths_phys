#include <stdio.h>
#include "vector3D_test.hpp"
#include "particle_test.hpp"

// Launcher of the Vector3D and Particle test

int main(){

  printf("Vector3D tests ... ");
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

  printf("done !\n");


  printf("Particle test ... \n");
  test_gun();

  printf("Done !\n");

  return 0;
}
