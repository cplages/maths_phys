#ifndef _OC_TREE_H_
#define _OC_TREE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"

struct bounding_sphere {
  Vector3D center;
  float radius;
};

class OcTree {
private:
  OcTree * children;
  int children_number;
  
  Vector3D position;
  Vector3D dimension;

  bounding_sphere * objects_contained;

  void create_children(OcTree * parent, int depth);

public:
  OcTree();
  OcTree(int depth, Vector3D p0, Vector3D d0);

  void add_sphere(Rigidbody r0);

  void display(OcTree * parent);

};

struct bounding_sphere rigidbody_to_sphere(Rigidbody r0);


#endif //_OC_TREE_H_
