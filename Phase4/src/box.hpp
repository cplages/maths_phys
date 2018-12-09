#ifndef _BOX_H_
#define _BOX_H_

#include "rigidbody.hpp"
#include "vector3D.hpp"
#include "primitive.hpp"
#include "matrix34.hpp"

class Box : public Primitive {
private:
  Vector3D half_size;

public:
  Box();
  Box(Rigidbody * r0, float width, float height, float deepness, Matrix34 offset);

  Vector3D get_half_size();

  Vector3D * get_vertices();

  Vector3D local_to_world(Vector3D point);

  bool primitive_in_octree(Vector3D p0, Vector3D d0);

};

  Vector3D * calculate_vertex_coordinate(Vector3D half_size);
#endif //BOX_H
