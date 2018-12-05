#ifndef _PLANE_H_
#define _PLANE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "primitive.hpp"

class Plane : public Primitive {
private:
  Vector3D half_size;

  int number_vertex_per_face = 4;
  int number_face = 6;
  
  Vector3D * vertex;

  void calculate_vertex_coordinate();
  
public:
  Plane();
  Plane(Rigidbody * r0, float width, float height, float deepness);

  Vector3D get_half_size();

  Vector3D * get_vertex();

  void display_vertex();
  
};

#endif //PLANE_H_
