#ifndef _PARTICULE_GRAVITY_GENERATOR_
#define _PARTICULE_GRAVITY_GENERATOR_

#include "particule_force_generator.hpp"

class ParticuleGravityGenerator : public ParticuleForceGenerator {

private :
  Vector3D gravity;

public :
  ParticuleGravityGenerator(Vector3D g0);
  void update_force(Particule * particule, float period); 
};


#endif
