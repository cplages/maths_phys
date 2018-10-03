#ifndef _PARTICLE_CONTACT_H_
#define _PARTICLE_CONTACT_H_

#include "vector3D.hpp"
#include "particle.hpp"


class ParticleContact {
private:
  Particle* particles[2];
  float coeff_restitution;
  Vector3D normal_vector;

  void resolve_velocity();
  void resolve_interpenetration();
  
public:
  ParticleContact(Particle* particle_a, Particle* particle_b, float coeff_restitution);
  
  void resolve(float period);

  float compute_vs();
  
};


#endif //_PARTICLE_CONTACT_H_
