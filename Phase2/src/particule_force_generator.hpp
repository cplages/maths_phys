#ifndef _PARTICULE_FORCE_GENERATOR_
#define _PARTICULE_FORCE_GENERATOR_

#include "particule.hpp"

class ParticuleForceGenerator {
public:
  virtual void update_force(Particule * particule, float period) = 0;
};

#endif 
