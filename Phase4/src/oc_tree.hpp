#ifndef _OC_TREE_H_
#define _OC_TREE_H_

#include "vector3D.hpp"
#include "rigidbody.hpp"
#include "primitive.hpp"
#include "sphere.hpp"
#include "collision_data.hpp"
#include "vector"


class OcTree {
private:
  OcTree * children;
  int children_number;

  Vector3D position;
  Vector3D dimension;

  std::vector<Primitive*> objects_contained;
  int nb_objects;

  void create_children(OcTree * parent, int depth);

  void broadphase(Primitive ** primitives, int size);
  void check_primitive(Primitive *  primitive);
  void narrowphase(CollisionData * data);

public:
  OcTree();
  OcTree(int depth, Vector3D p0, Vector3D d0);

  void check_collision(Primitive ** primitives, int size);

  void apply_narrow_phase(CollisionData * data);

  void display(OcTree * parent);

  void reset_object_array();

};


#endif //_OC_TREE_H_
