#include "force_register.hpp"

void ForceRegister::add(Particle *particle, ParticleForceGenerator *fg) {
  struct ForceRecording tmp;
  tmp.particle = particle;
  tmp.fg = fg;
  forces.push_back(tmp);
}

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

int ForceRegister::count() {
  return forces.size();
}

ForceRegister::records ForceRegister::get_force_register(){
  return forces;
}
