#ifndef _PARTICLE_
#define _PARTICLE_

#include "vector3D.hpp"

/* Class representing a particle

Attributes : position, velocity, acceleration, inverse_mass, gravity and dumping

Particular methods : integrate (update position and velocity of the particle at each frame)

*/

class Particle {

private:
  Vector3D position;
  Vector3D velocity;
  Vector3D acceleration;
  float inverse_mass;
  float radius;

  Vector3D accum_force; //resulting force
  // Vector3D gravity; //Float in constructor convert to Vector in attributes
  // float dumping;

public:
  Particle();
  Particle(Vector3D p0, Vector3D v0, Vector3D a0, float m0, float r);

  Vector3D get_position();
  void set_position(Vector3D p0);

  Vector3D get_velocity();
  void set_velocity(Vector3D v0);

  float get_inverse_mass();
  void set_mass(float m0);

  float get_radius();

  void integrate(float t);

  void add_force(const Vector3D &force);
  void clear_accum();

  void display();

  float get_interpenetration_with(Particle * p);


  ~Particle();

  Particle& operator =(Particle const& p);


};

#endif
