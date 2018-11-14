#ifndef _PARTICLE_CONTACT_H_
#define _PARTICLE_CONTACT_H_

#include "vector3D.hpp"
#include "particle.hpp"


class ParticleContact {
private:
  Particle* particles[2];
  float coeff_restitution;
  Vector3D normal_vector;
  float penetration;

  //true if the contact is from a cable
  bool contact_cable;

  void resolve_velocity();
  void resolve_interpenetration();
  void resolve(float period);

  friend class ParticleContactResolver;

public:

  ParticleContact(Particle* particle_a, Particle* particle_b, float coeff_restitution, float penetration, bool contact_cable);

  float compute_vs();

};


#endif //_PARTICLE_CONTACT_H_
