#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>

/* class responsible for the physic of the game*/
class GameWorld {

private:
  bool demo_1;
  bool collision;
  ForceRegister * rigidbodies_and_forces;

  Rigidbody * main_rigidbody;
  Rigidbody * second_rigidbody;
  RigidbodyGravityGenerator * gravity_generator;

  void init();
public:
  GameWorld();

  Rigidbody* get_main_rigidbody();
  Rigidbody* get_second_rigidbody();
  void execute(float * current_time);
  void call_all_force_generator();

  void change_demo();
};



#endif
