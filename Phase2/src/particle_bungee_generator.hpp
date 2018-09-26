#ifndef _PARTICULE_BUNGEE_GENERATOR_
#define _PARTICULE_BUNGEE_GENERATOR_

#include "particule_force_generator.hpp"

class ParticuleBungeeGenerator : public ParticuleSpringGenerator {

public :
  ParticuleBungeeGenerator(Vector3D anchored_point);
  void update_force(Particule * particule, float period); 
};


#endif
