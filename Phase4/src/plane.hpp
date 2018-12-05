#ifndef _PLANE_H_
#define _PLANE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "primitive.hpp"

class Plane : public Primitive {
private:
  Vector3D normal;
  float offset;

public:
  Plane();
  Plane(Vector3D n, float o);

  Vector3D get_normal();
  float get_offset();

  float get_distance_from_point(Vector3D point);
};

#endif //PLANE_H_
