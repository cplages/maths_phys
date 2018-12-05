#ifndef _BOX_H_
#define _BOX_H_

#include "rigidbody.hpp"
#include "primitive.hpp"

class Box : public Primitive {
private:
  float distance_center_to_face;

public:
  Box();
  Box(Rigidbody * r0, float s0);

  float get_distance();
  
};

#endif //BOX_H
