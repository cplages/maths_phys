#include <stdio.h>
#include <assert.h>

#include "../src/particle.hpp"

//test which print the particle information or a simulated animation
void test_gun(){
  float interval = 0.0333;
  float time = 0;
  Particle gun_bullet = Particle(Vector3D(), Vector3D(35,0,0), Vector3D(0, -10, 0), 1);

  for(int i = 0; i<10; i++){
    time = i * interval;
    printf("Time = %f\n", time);
    gun_bullet.integrate(time);
    gun_bullet.display();
  }

}
