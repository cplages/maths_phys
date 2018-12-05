#ifndef _CONTACT_H_
#define _CONTACT_H_

#include "vector3D.hpp"

class Contact {

private:
  Vector3D contact_point;
  Vector3D contact_normal;
  float penetration;

public:

  Contact();
  Contact(Vector3D cp, Vector3D cn, float p);




};

#endif // _CONTACT_H_
