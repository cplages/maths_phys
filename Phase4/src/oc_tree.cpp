#include <stdio.h>
#include <stdlib.h>

#include "oc_tree.hpp"

OcTree::OcTree() {
}

OcTree::OcTree(int depth, Vector3D p0, Vector3D d0) {

  children = NULL;
  children_number = 8;
  position = p0;
  dimension = d0;

  create_children(this, depth);
  

}

//believe the salmon faith
void OcTree::create_children(OcTree * parent, int depth) {

  if( depth != 0) {
    Vector3D dimension_children = parent->dimension / 2;

    float x_parent = parent->position.get_x();
    float y_parent = parent->position.get_y();
    float z_parent = parent->position.get_z();
  
    float x_child = 0;
    float y_child = 0;
    float z_child = 0;

    parent->children = new OcTree[children_number];
    for(int i = 0 ; i < 2; ++i) {
      x_child = x_parent + i * dimension_children.get_x() - dimension_children.get_x() / 2;
      for(int j = 0; j < 2; ++j) {
	y_child = y_parent + j * dimension_children.get_y() - dimension_children.get_y() / 2;
	for(int k = 0; k < 2; ++k) {
	  z_child = z_parent + k * dimension_children.get_z()  - dimension_children.get_z() / 2;

	  int index = i * 4 + j * 2 + k;
	  printf("%d\n",index);
	  parent->children[index] = OcTree(depth - 1, Vector3D(x_child, y_child, z_child), dimension_children);
	    }
      }
    }
  }
  
}


void OcTree::display(OcTree * parent) {
  printf("Octree: \n");
  printf("position = \t");
  parent->position.display();

  printf("dimension = \t");
  parent->dimension.display();

  printf("\n");

  if(parent->children != NULL) {
    for(int i = 0 ; i < children_number; ++i)
      {
	printf("child %d \n", i);
	display(parent->children + i);
      }
  }
  
}
  
