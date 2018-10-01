#ifndef _FORCE_REGISTER_
#define _FORCE_REGISTER_

#include <vector>

#include "particle.hpp"
#include "particle_force_generator.hpp"

class ForceRegister {
public:

  struct ForceRecording {
    Particle *particle;
    ParticleForceGenerator *fg;
  };
  typedef std::vector<struct ForceRecording> records;
  records forces;


  void add(Particle *particle, ParticleForceGenerator *fg);
  void erase(Particle *particle, ParticleForceGenerator *fg);
  int count();

  records get_force_register();
};

#endif
