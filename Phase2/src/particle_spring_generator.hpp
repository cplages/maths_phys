#ifndef _PARTICULE_SPRING_GENERATOR_
#define _PARTICULE_SPRING_GENERATOR_

#include "particule_force_generator.hpp"

class ParticuleSpringGenerator : public ParticuleForceGenerator {

private :
  Particule other_particle;
  float k;
  float l0;

public :
  ParticuleSpringGenerator(Particule other_particle, float k, float l0);
  virtual void update_force(Particule * particule, float period); 
};


#endif
