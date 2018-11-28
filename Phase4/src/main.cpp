#include "oc_tree.hpp"
#include "vector3D.hpp"


int main() {
  OcTree octree = OcTree(1, Vector3D(0,0,0), Vector3D(20, 20, 20));

  octree.display(&octree);
  return 0;
}
