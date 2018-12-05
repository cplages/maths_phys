#ifndef _OC_TREE_H_
#define _OC_TREE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "primitive.hpp"

class OcTree {
private:
  OcTree * children;
  int children_number;
  
  Vector3D position;
  Vector3D dimension;

  Primitive * objects_contained;

  void create_children(OcTree * parent, int depth);

public:
  OcTree();
  OcTree(int depth, Vector3D p0, Vector3D d0);

  void add_sphere(Rigidbody r0);

  void display(OcTree * parent);

};


#endif //_OC_TREE_H_
