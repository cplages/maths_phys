#ifndef _FORCE_REGISTER_
#define _FORCE_REGISTER_

#include <vector>

#include "particule.hpp"
#include "particule_force_generator.hpp"

class ForceRegister {
private:
  struct ForceRecording {
    Particule *particule;
    ParticuleForceGenerator *fg;
  };
  
  typedef std::vector<struct ForceRecording> records;
  records forces;
   
public:
  void add(Particule *particule, ParticuleForceGenerator *fg);
  void erase(Particule *particule, ParticuleForceGenerator *fg);
  int count();
};

#endif
