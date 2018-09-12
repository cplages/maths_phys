#ifndef _PARTICULE_
#define _PARTICULE_

#include "vector3D.hpp"

/* Class representing a particule

Attributes : position, velocity, acceleration, inverse_mass, gravity and dumping

Particular methods : integrate (update position and velocity of the particule at each frame)

*/

class Particule {

private:
  Vector3D position;
  Vector3D velocity;
  Vector3D acceleration;
  float inverse_mass;
  Vector3D gravity; //Float in constructor convert to Vector in attributes
  float dumping;

public:
  Particule();
  Particule(Vector3D p0, Vector3D v0, float m0, float g0, float d0);

  Vector3D get_position();
  float get_inverse_mass();
  void set_mass(float m0);
  void integrate(float t);
  void display();
  ~Particule();

  Particule& operator =(Particule const& p);
};

#endif
