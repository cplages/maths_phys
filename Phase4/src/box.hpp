#ifndef _BOX_H_
#define _BOX_H_

#include "rigidbody.hpp"
#include "vector3D.hpp"
#include "primitive.hpp"

class Box : public Primitive {
private:
  Vector3D half_size;

  Vector3D * calculate_vertex_coordinate();


public:
  Box();
  Box(Rigidbody * r0, float width, float height, float deepness);

  Vector3D get_half_size();

  Vector3D * get_vertices();

  void display_vertex();

  Vector3D local_to_world(Vector3D point);



};

#endif //BOX_H
