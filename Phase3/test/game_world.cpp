#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <cstddef>
#include <limits>

#include "../src/vector3D.hpp"
#include "../src/rigidbody.hpp"
#include "../src/matrix33.hpp"
#include "../src/matrix34.hpp"
#include "../src/quaternion.hpp"
#include "../src/rigidbody_force_generator.hpp"
#include "../src/rigidbody_gravity_generator.hpp"
#include "../src/force_register.hpp"
#include "../src/constant.hpp"

#include "game_world.hpp"

using namespace std;

//init rigidbodys, forces generator(spring, gravity) and cables
GameWorld::GameWorld(){
  rigidbodies_and_forces = new ForceRegister();

  // Main rigidbody subjected to gravity
  int dx = 1;
  int dy = 1;
  int dz = 1;
  float m = 10;
  Matrix33 rectangle_tensor = Matrix33((1/12) * m * (pow(dy,2) + pow(dz,2)), 0, 0, 0, (1/12) * m * (pow(dx,2) + pow(dz,2)), 0, 0, 0, (1/12) * m * (pow(dx,2) + pow(dy,2)));
  
  main_rigidbody = new Rigidbody(Vector3D(), Vector3D(0, 0, 11), Vector3D(), m, 1, 1, Quaternion(sqrt(2)/2,0,0,sqrt(2)/2), Matrix34::identity_matrix(), rectangle_tensor.inverse());
  
  gravity_generator = new RigidbodyGravityGenerator(Vector3D(0,GRAVITY_VALUE,0));
  rigidbodies_and_forces->add(main_rigidbody, gravity_generator);

}


Rigidbody* GameWorld::get_rigidbody(){
  return main_rigidbody;
}

//update physic at each frame.
void GameWorld::execute(float * current_time){
  clock_t start_time = clock();

  // Call force generators
  call_all_force_generator();

  // Integration of every rigidbody
  main_rigidbody->integrate(FRAME_INTERVAL);


  //update time
  (*current_time) += FRAME_INTERVAL;
  float remaining_time = FRAME_INTERVAL - (clock() - start_time) / CLOCKS_PER_SEC;
  if(remaining_time > 0) {
    //multiply by 1000 due to sleep function taking millisecond in argument.
    usleep(remaining_time * 1000);
  }

}

void GameWorld::call_all_force_generator()
{
  ForceRegister::records forces = rigidbodies_and_forces->get_force_register();

  for(ForceRegister::records::iterator it = forces.begin(); it != forces.end(); ++it)
    {
      RigidbodyForceGenerator* current_force = it->fg;
      Rigidbody * current_rigidbody = it->rigidbody;
      current_force->update_force(current_rigidbody, FRAME_INTERVAL);
    }
}
