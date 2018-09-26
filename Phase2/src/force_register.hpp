#ifndef _FORCE_REGISTER_
#define _FORCE_REGISTER_

#include <vector>

#include "particule.hpp"
#include "particule_force_generator.hpp"

class ForceRegister {
public:

  struct ForceRecording {
    Particule *particule;
    ParticuleForceGenerator *fg;
  };
  typedef std::vector<struct ForceRecording> records;
  records forces;
  
  
  void add(Particule *particule, ParticuleForceGenerator *fg);
  void erase(Particule *particule, ParticuleForceGenerator *fg);
  int count();

  records get_force_register();
};

#endif
