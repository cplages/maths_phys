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


GameWorld::GameWorld(int n, float radius_particle){
  /* INIT PARTICLES AND FORCES */
  this->particle_number = n;
  particles_and_forces = new ForceRegister();


  //float floor_mass = std::numeric_limits<float>::max();
  //create floor
  //floor_particle = new Particle(Vector3D(0, -40.0, 0), Vector3D(), Vector3D(), floor_mass, radius_particle);
  // Main particle subjected to gravity
  main_particle = new Particle(Vector3D(), Vector3D(), Vector3D(), 1, radius_particle);
  gravity_generator = new ParticleGravityGenerator(Vector3D(0,-0.05,0));
  particles_and_forces->add(main_particle, gravity_generator);

  // Sub particles following the main particle
  // subjected to spring forces
  spring_generator = new ParticleSpringGenerator(main_particle, 0.1, 4); //valeurs arbitraires zouglou

  // Init of sub particles
  for (int i = 0; i<this->particle_number-1; i++){
    sub_particles.push_back(new Particle(Vector3D((i+2),0,0), Vector3D(), Vector3D(), 1, radius_particle));
    particles_and_forces->add(sub_particles[i], spring_generator);
    Particle * cable_ends[2];
    cable_ends[0] = main_particle;
    cable_ends[1] = sub_particles[i];
    // add cable contact between every sub and the main particle
    cable_generators.push_back(new ParticleCable(cable_ends, 100000, 0.1)); //zouglou
  }
}

std::vector<Particle*> GameWorld::get_active_particles(){
  std::vector<Particle*> tmp = std::vector<Particle*>(sub_particles);
  tmp.push_back(main_particle);
  return tmp;
}

void GameWorld::execute(float * current_time){
  main_particle->get_position().display();
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
   /*if(all_particles[i]->get_position().get_y() <= floor_particle->get_position().get_y()) {
     float floor_mass = std::numeric_limits<float>::max();
     floor_particle = new Particle(Vector3D(all_particles[i]->get_position().get_x(), -40.0, 0), Vector3D(), Vector3D(), floor_mass, 1);
     particle_contacts.push_back(new ParticleContact(all_particles[i], floor_particle, 10, 1));
     //delete floor_particle;
   }*/
    for (int j = 0; j<size; j++){
      if (i != j){
        float penetration = all_particles[i]->get_interpenetration_with(all_particles[j]);
        if (penetration > 0){
          particle_contacts.push_back(new ParticleContact(all_particles[i], all_particles[j], 0.01, penetration));
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
