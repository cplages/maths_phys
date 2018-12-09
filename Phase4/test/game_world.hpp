#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include "../src/box.hpp"
#include "../src/oc_tree.hpp"

/* class responsible for the physic of the game*/
class GameWorld {

private:
  ForceRegister * rigidbodies_and_forces;
  Box * main_box;
  CollisionData *datas;
  RigidbodyGravityGenerator * gravity_generator;
  Plane * walls;
  OcTree * octree;

  //tab of all primitives in game
  Primitive ** primitives;
  void init(Vector3D velocity);

public:
  GameWorld(Vector3D velocity);

  Box * get_main_box();
  Plane * get_walls();

  void execute(float * current_time);

  void call_all_force_generator();

  bool collision_occured();

  Vector3D get_normal_contact();

  void display_contact();
};

#endif
