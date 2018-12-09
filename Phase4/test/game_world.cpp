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
#include "../src/primitive.hpp"
#include "../src/oc_tree.hpp"
#include "../src/box.hpp"
#include "../src/plane.hpp"

#include "game_world.hpp"

using namespace std;


GameWorld::GameWorld(Vector3D velocity){
  init(velocity);
}

//Init walls and box
void GameWorld::init(Vector3D velocity){

  rigidbodies_and_forces = new ForceRegister();

  int dx = 1;
  int dy = 1;
  int dz = 1;
  float m = 10;
  Matrix33 rectangle_tensor = Matrix33((1/12.) * m * (pow(dy,2) + pow(dz,2)), 0, 0, 0, (1/12.) * m * (pow(dx,2) + pow(dz,2)), 0, 0, 0, (1/12.) * m * (pow(dx,2) + pow(dy,2)));

  Rigidbody * main_rigidbody = new Rigidbody(Vector3D(0, 0, 0), Vector3D(0.5, 0.5, 0.5), velocity, m, 0.9, 0.9, Quaternion(1,0,0,0), Matrix34::identity_matrix(), rectangle_tensor.inverse());

  gravity_generator = new RigidbodyGravityGenerator(Vector3D(0,GRAVITY_VALUE,0));
  rigidbodies_and_forces->add(main_rigidbody, gravity_generator);

  main_box =  new Box(main_rigidbody, dx, dy, dz, Matrix34::identity_matrix());

  walls = new Plane[5];
  float room_size = 5;
  walls[0] = Plane(Vector3D(1,0,0),room_size);
  walls[1] = Plane(Vector3D(0,1,0), room_size);
  walls[2] = Plane(Vector3D(0,0,1), room_size);
  walls[3] = Plane(Vector3D(0,-1,0), room_size);
  walls[4] = Plane(Vector3D(-1,0,0), room_size);

  primitives = new Primitive*[6];

  for(int i = 0; i < 5; ++i) {
    primitives[i] = &walls[i];
  }
  primitives[5] = main_box;

  octree =  new OcTree(1, Vector3D(), Vector3D(11,11,11));

  datas = new CollisionData(20);
}

Box * GameWorld::get_main_box(){
  return main_box;
}

Plane * GameWorld::get_walls(){
  return walls;
}

//update physic at each frame.
void GameWorld::execute(float * current_time){
  clock_t start_time = clock();

    // Call force generators
  call_all_force_generator();

  // Integration of every rigidbody
  main_box->get_rigidbody()->integrate(FRAME_INTERVAL);

  //check collision broadphase
  octree->check_collision(primitives, 6);

  //check collision narrowphase
  octree->apply_narrow_phase(datas);

  //reset octree
  octree->reset_object_array();

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

bool GameWorld::collision_occured() {
  return datas->get_current_size() != 0;
}

Vector3D GameWorld::get_normal_contact() {
  return datas->get_contact().get_normal();
}

void GameWorld::display_contact() {
  datas->get_contact().display();
}
