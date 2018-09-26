#include "force_register.hpp"

void ForceRegister::add(Particule *particule, ParticuleForceGenerator *fg) {
  struct ForceRecording tmp;
  tmp.particule = particule;
  tmp.fg = fg;
  forces.push_back(tmp);
}

void ForceRegister::erase(Particule *particule, ParticuleForceGenerator *fg) {
  struct ForceRecording tmp;
  tmp.particule = particule;
  tmp.fg = fg;

  bool found = false;
  records::iterator it = forces.begin();
  while (it != forces.end() && !found) {
    if((it->particule == tmp.particule) && (it->fg == tmp.fg)) {
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

