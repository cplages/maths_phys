#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <vector>

#include "collision_data.hpp"
#include "primitive.hpp"
#include "oc_tree.hpp"
#include "box.hpp"
#include "plane.hpp"
#include "math.h"

OcTree::OcTree() {
}

OcTree::OcTree(int depth, Vector3D p0, Vector3D d0) {
  children = NULL;
  children_number = 8;
  position = p0;
  dimension = d0;
  nb_objects = 0;

  create_children(this, depth);
}

//Create recursively the octree
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
          parent->children[index] = OcTree(depth - 1, Vector3D(x_child, y_child, z_child), dimension_children);
        }
      }
    }
  }

}

// Lauch broadphase detection step for all the leaves of the octree
void OcTree::check_collision(Primitive ** primitives, int size) {
  if(children != NULL) {
    for(int i = 0; i < 8; ++i) {
      children[i].check_collision(primitives, size);
    }
  }
  else {
    broadphase(primitives, size);
  }
}

// Apply broadphase on all primitives
void OcTree::broadphase(Primitive ** primitives, int size){
  for(int i = 0; i < size; ++i) {
    check_primitive(primitives[i]);
  }
}

//Add potential collisions objects
void OcTree::check_primitive(Primitive * primitive) {
  //formula primitive and box detection
  if(primitive->primitive_in_octree(position,dimension))
  {
    objects_contained.push_back(primitive);
    nb_objects++;
  }
}

// Lauch narrowphase detection step for all the leaves of the octree
void OcTree::apply_narrow_phase(CollisionData * data)
{
  if(children != NULL) {
    for(int i = 0; i < 8; ++i) {
      children[i].apply_narrow_phase(data);
    }
  }
  else {
    narrowphase(data);
  }
}

// Apply narrowphase between all primitives contained in the leaf
void OcTree::narrowphase(CollisionData * data)
{
  if(nb_objects > 1)
  {
    for(int i = 0; i < nb_objects; ++i) {
      for(int j = 0; j < nb_objects; ++j) {
        //Check only for box and planes collisions (avoid plane/plane collisions)
        if(i != j && typeid(*objects_contained[i]) == typeid(Box) ) {
          generate_contacts(dynamic_cast<Box *>(objects_contained[i]), dynamic_cast<Plane *>(objects_contained[j]), data);
        }
      }
    }
  }
}


//Prepare the octree for the next physic update
void OcTree::reset_object_array() {
  objects_contained.clear();
  nb_objects = 0;
  if(children!= NULL) {
    for(int i = 0; i < 8; ++i) {
      children[i].reset_object_array();
    }
  }
}

void OcTree::display(OcTree * parent) {
  printf("Octree: \n");
  printf("position = \t");
  parent->position.display();

  printf("dimension = \t");
  parent->dimension.display();

  printf("object number = \t%d\n", parent->nb_objects);

  printf("\n");

  if(parent->children != NULL) {
    for(int i = 0 ; i < children_number; ++i)
      {
	       printf("child %d \n", i);
	       display(parent->children + i);
      }
  }

}
