#include "vector3D.hpp"

#include "particle_buoyancy_generator.hpp"


ParticleBuoyancyGenerator::ParticleBuoyancyGenerator(float max_deepness, float object_volume, float water_height, float density){
  this->max_deepness = max_deepness;
  this->object_volume = object_volume;
  this->water_height = water_height;
  this->density = density;
}

void ParticleBuoyancyGenerator::update_force(Particle * particle, float period){

  float subversion; //  ?
  Vector3D force;

  if (subversion <= 0){
    force = Vector3D();
  }
  else if (subversion >= 1){
    // vol * d

  }
  else {
    // subversion * vol * d
  }

  particle->add_force(force);
}
