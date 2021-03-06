#include <cstdio>
#include <limits>

#include "particle_contact.hpp"

ParticleContact::ParticleContact(Particle* particle_a, Particle* particle_b, float coeff_restitution, float penetration, bool contact_cable): coeff_restitution(coeff_restitution), penetration(penetration)
{
  particles[0] = particle_a;
  particles[1] = particle_b;

  this->contact_cable = contact_cable;

  Vector3D p1;
  if(particles[1] != NULL) {
    p1 = particles[1]->get_position();
  }
  //if the particle collides with the ground...
  else {
    //set p to the lowest part of the particle.
    p1 = Vector3D(particles[0]->get_position().get_x(), particles[0]->get_position().get_y()- particles[0]->get_radius(), particles[0]->get_position().get_z());
  }

  //compute normal
  Vector3D distance_vector = (particles[0]->get_position() - p1);
  normal_vector = distance_vector * (1 / distance_vector.norm());

  //normal inversion
  if(contact_cable) {
    normal_vector = normal_vector * -1;
  }
}

void ParticleContact::resolve_velocity()
{
  //compute vs
  float vs_old = compute_vs();
  float vs = (-coeff_restitution * vs_old);

  //set new velocity to the first particle
  Vector3D old_v0 = particles[0]->get_velocity();
  Vector3D vs0;
  vs0 = normal_vector * vs;
  
  particles[0]->set_velocity(old_v0 + (vs0 * particles[0]->get_inverse_mass()));
  
  //if the particle doesn't collide with the ground...
  if(particles[1] != NULL) {
    //set new velocity to the second particle
    Vector3D old_v1 = particles[1]->get_velocity();
    Vector3D vs1;
    
    vs1 = normal_vector * vs * -1;
    particles[1]->set_velocity(old_v1 + (vs1 * particles[1]->get_inverse_mass()));
  }
}

void ParticleContact::resolve_interpenetration()
{
  float ma = 1 / particles[0]->get_inverse_mass();
  float mb;

  //get particle mass
  if(particles[1] != NULL) {
    mb = 1 / particles[1]->get_inverse_mass();
  }
  //if the particle collides with the ground...
  else {
    //ground mass equal to the max value possible
    mb = std::numeric_limits<float>::max();
  }

  //set position to the first particle
  Vector3D delta_pa = normal_vector * ((mb / (ma + mb)) * penetration);
  Vector3D new_pa = particles[0]->get_position() + delta_pa;
  particles[0]->set_position(new_pa);

  //if the particle doesn't collide with the ground...
  if(particles[1] != NULL) {
    //set position to the second particle
    Vector3D delta_pb = normal_vector * ((ma / (ma + mb)) * penetration) * -1;
    Vector3D new_pb = particles[1]->get_position() + delta_pb;
    particles[1]->set_position(new_pb);
  }
}

void ParticleContact::resolve(float period)
{
  resolve_velocity();
  if (penetration > 0){
    resolve_interpenetration();
  }
}

float ParticleContact::compute_vs()
{
  Vector3D v1;

  if(particles[1] != NULL) {
    v1 = particles[1]->get_velocity();
  }
  //if the particle collides with the ground...
  else {
    //the ground doesn't have a velocity
    v1 = Vector3D();
  }
  Vector3D velocity_diff= particles[0]->get_velocity() - v1;
  return ((velocity_diff).dot_product(&(normal_vector)));
}
