#include "vector3D.hpp"
#include "particle_link.hpp"

float ParticleLink::get_length()
{
  Vector3D p1_pos = particles[1]->get_position();
  return (particles[0]->get_position()).distance(&p1_pos);
}

