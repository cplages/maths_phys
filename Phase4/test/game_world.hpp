#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>

/* class responsible for the physic of the game*/
class GameWorld {

private:
  ForceRegister * rigidbodies_and_forces;

  Rigidbody * main_rigidbody;

  RigidbodyGravityGenerator * gravity_generator;


  void init();
public:
  GameWorld();

  Rigidbody* get_main_rigidbody();

  void execute(float * current_time);

  void call_all_force_generator();

};

#endif
