#include "particle_contact.hpp"

ParticleContact::ParticleContact(Particle* particle_a, Particle* particle_b, float coeff_restitution): coeff_restitution(coeff_restitution)
{
  particles[0] = particle_a;
  particles[1] = particle_b;
  Vector3D distance_vector = (particles[0]->get_position() - particles[1]->get_position());
  normal_vector = distance_vector * (1 / distance_vector.norm()) ;
}

void ParticleContact::resolve_velocity()
{
  float vs_old = compute_vs();
  float vs = (-coeff_restitution * vs_old);
 
  particles[0]->set_velocity(normal_vector * vs);
  particles[1]->set_velocity(normal_vector * -vs);
}

void ParticleContact::resolve_interpenetration()
{
  
}  

void ParticleContact::resolve(float period)
{
  
}

float ParticleContact::compute_vs()
{
  Vector3D velocity_diff= particles[0]->get_velocity() - particles[1]->get_velocity();
  return ((velocity_diff).dot_product(&(normal_vector)));
}
  
