#include "force_register.hpp"

//add a force to apply to a particle in the register.
void ForceRegister::add(Particle *particle, ParticleForceGenerator *fg) {
  struct ForceRecording tmp;
  tmp.particle = particle;
  tmp.fg = fg;
  forces.push_back(tmp);
}

//remove a force applied to a particle from the register.
void ForceRegister::erase(Particle *particle, ParticleForceGenerator *fg) {
  struct ForceRecording tmp;
  tmp.particle = particle;
  tmp.fg = fg;

  bool found = false;
  records::iterator it = forces.begin();
  while (it != forces.end() && !found) {
    if((it->particle == tmp.particle) && (it->fg == tmp.fg)) {
      found = true;
      forces.erase(it);
    }
  }
}

//size of the register.
int ForceRegister::count() {
  return forces.size();
}

//return the register.
ForceRegister::records ForceRegister::get_force_register(){
  return forces;
}
