#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <cstddef>
#include <limits>

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

//init particles, forces generator(spring, gravity) and cables
GameWorld::GameWorld(int n, float radius_particle){
  this->particle_number = n;
  particles_and_forces = new ForceRegister();

  // Main particle subjected to gravity
  main_particle = new Particle(Vector3D(), Vector3D(), Vector3D(), 10, radius_particle);
  gravity_generator = new ParticleGravityGenerator(Vector3D(0,GRAVITY_VALUE,0));
  particles_and_forces->add(main_particle, gravity_generator);

  // Sub particles following the main particle
  //init spring generator
  spring_generator = new ParticleSpringGenerator(main_particle, 0.1, 4);

  // Init of sub particles
  for (int i = 0; i<this->particle_number-1; i++){
    sub_particles.push_back(new Particle(Vector3D((i-this->particle_number/2)*2 + radius_particle * 1.2, 0, 0), Vector3D(), Vector3D(), 1, radius_particle));
    
    particles_and_forces->add(sub_particles[i], gravity_generator);
    particles_and_forces->add(sub_particles[i], spring_generator);
    
    Particle * cable_ends[2];
    cable_ends[0] = main_particle;
    cable_ends[1] = sub_particles[i];
    // add cable contact between every sub and the main particle
    cable_generators.push_back(new ParticleCable(cable_ends, 0.5, 5));
  }
}

//return all particles, add the main particle at the back of the sub_particle array.
std::vector<Particle*> GameWorld::get_active_particles(){
  std::vector<Particle*> tmp = std::vector<Particle*>(sub_particles);
  tmp.push_back(main_particle);
  return tmp;
}

//update physic at each frame.
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

  // Add simple contacts between particles
  std::vector<ParticleContact*> particle_contacts;
  std::vector<Particle*> all_particles = get_active_particles();
  int size = all_particles.size();
  for (int i = 0; i<size; i++){
    //simulate floor.
    if(all_particles[i]->get_position().get_y() - all_particles[i]->get_radius() <= FLOOR_HEIGHT) {
      particle_contacts.push_back(new ParticleContact(all_particles[i], NULL, 0.25, 0.005/*all_particles[i]->get_radius() + FLOOR_HEIGHT - all_particles[i]->get_position().get_y()*/, false));
    
      }
    for (int j = 0; j<size; j++){
      //check if two particles are in collision.
      if (i != j){
        float penetration = all_particles[i]->get_interpenetration_with(all_particles[j]);
        if (penetration > 0){
	  //if it is the case, create contact.
	  particle_contacts.push_back(new ParticleContact(all_particles[i], all_particles[j], 0.9, penetration, false));
        }
      }
    }
  }

  // Add cable contacts between particles
  for(vector<ParticleCable *>::iterator it = cable_generators.begin(); it != cable_generators.end(); ++it)
  {
    ParticleContact * tmp = (*it)->add_contact();
    if(tmp != NULL)
    {
      particle_contacts.push_back(tmp);
    }
  }

  // Resolve contacts
  ParticleContactResolver * resolver = new ParticleContactResolver(particle_contacts);
  resolver->resolve_contacts();

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
  ForceRegister::records forces = particles_and_forces->get_force_register();

  for(ForceRegister::records::iterator it = forces.begin(); it != forces.end(); ++it)
    {
      ParticleForceGenerator* current_force = it->fg;
      Particle * current_particle = it->particle;
      current_force->update_force(current_particle, FRAME_INTERVAL);
    }
}
