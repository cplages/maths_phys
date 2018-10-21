#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include "../src/particle.hpp"
#include "../src/particle_contact_generator.hpp"
#include "../src/particle_contact_resolver.hpp"
#include "../src/particle_spring_generator.hpp"
#include "../src/particle_cable.hpp"

class GameWorld {

private:
  int particle_number;

  ForceRegister * particles_and_forces;

  Particle * main_particle;
  ParticleGravityGenerator * gravity_generator;

  std::vector<Particle*> sub_particles;
  ParticleSpringGenerator * spring_generator;

  std::vector<ParticleCable *> cable_generators;


public:
  GameWorld(int n);

  std::vector<Particle*> get_active_particles();
  void execute(float * current_time);
  void call_all_force_generator();

};



#endif
