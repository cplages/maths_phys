#ifndef _PARTICULE_DRAG_GENERATOR_
#define _PARTICULE_DRAG_GENERATOR_

#include "particule_force_generator.hpp"

class ParticuleDragGenerator : public ParticuleForceGenerator {

private :
  float k1;
  float k2;

public :
  ParticuleDragGenerator(float k1, float k2);
  void update_force(Particule * particule, float period); 
};


#endif
