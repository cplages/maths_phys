#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <cstddef>

#include "../src/vector3D.hpp"
#include "../src/particle.hpp"
#include "../src/particle_force_generator.hpp"
#include "../src/particle_gravity_generator.hpp"
#include "../src/particle_spring_generator.hpp"
#include "../src/particle_cable.hpp"
#include "../src/force_register.hpp"
#include "../src/constant.hpp"

#include "game_world.hpp"

using namespace std;


GameWorld::GameWorld(int n){
  /* INIT PARTICLES AND FORCES */
  this->particle_number = n;
  particles_and_forces = new ForceRegister();

  // Main particle subjected to gravity
  main_particle = new Particle(Vector3D(), Vector3D(), Vector3D(), 2);
  gravity_generator = new ParticleGravityGenerator(Vector3D(0,-5,0));
  particles_and_forces->add(main_particle, gravity_generator);

  // Sub particles following the main particle
  // subjected to spring forces
  spring_generator = new ParticleSpringGenerator(*main_particle, 3, 10); //valeurs arbitraires zouglou

  // Init of sub particles
  for (int i = 0; i<this->particle_number-1; i++){
    sub_particles.push_back(new Particle(Vector3D(2.0,0,0), Vector3D(), Vector3D(), 2));
    particles_and_forces->add(sub_particles[i], spring_generator);
    Particle * cable_ends[2];
    cable_ends[0] = main_particle;
    cable_ends[1] = sub_particles[i];
    // add cable contact between every sub and the main particle
    cable_generators.push_back(new ParticleCable(cable_ends, 2, 0.5)); //zouglou
  }
}

std::vector<Particle*> GameWorld::get_active_particles(){
  std::vector<Particle*> tmp = std::vector<Particle*>(sub_particles);
  tmp.push_back(main_particle);
  return tmp;
}

void GameWorld::execute(float * current_time){
  clock_t start_time = clock();

  // Call force generators
  call_all_force_generator();

  // Integration of every particle
  main_particle->integrate(FRAME_INTERVAL);

  for(vector<Particle *>::iterator it = sub_particles.begin(); it != sub_particles.end(); ++it)
  {
    (*it)->integrate(FRAME_INTERVAL);
  }

  // Add contacts between particles
  std::vector<ParticleContact*> particle_contacts;
  for(vector<ParticleCable *>::iterator it = cable_generators.begin(); it != cable_generators.end(); ++it)
  {
    ParticleContact * tmp = (*it)->add_contact();
    if(tmp != NULL)
    {
        particle_contacts.push_back(tmp);
    }

  }
  // Resolve contact
  ParticleContactResolver * resolver = new ParticleContactResolver(particle_contacts);
  resolver->resolve_contacts();

  (*current_time) += FRAME_INTERVAL;
  float remaining_time = FRAME_INTERVAL - (clock() - start_time) / CLOCKS_PER_SEC;
  if(remaining_time > 0) {
    //multiply by 1000 due to sleep function taking millisecond in argument.
    usleep(remaining_time * 1000);
  }

}

void GameWorld::call_all_force_generator()
{
  ForceRegister::records forces = particles_and_forces->get_force_register();

  for(ForceRegister::records::iterator it = forces.begin(); it != forces.end(); ++it)
    {
      ParticleForceGenerator* current_force = it->fg;
      Particle * current_particle = it->particle;
      current_force->update_force(current_particle, FRAME_INTERVAL);
    }
}
