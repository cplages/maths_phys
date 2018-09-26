#ifndef _PARTICULE_ANCHORED_SPRING_GENERATOR_
#define _PARTICULE_ANCHORED_SPRING_GENERATOR_

#include "particule_force_generator.hpp"

class ParticuleAnchoredSpringGenerator : public ParticuleForceGenerator {

private :
  Vector3D anchored_point;

public :
  ParticuleAnchoredSpringGenerator(Vector3D anchored_point);
  void update_force(Particule * particule, float period); 
};


#endif
