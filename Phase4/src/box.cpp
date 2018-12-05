#include "rigidbody.hpp"
#include "primitive.hpp"
#include "box.hpp"

Box::Box(): Primitive()
{
  distance_center_to_face = 0;
}

Box::Box(Rigidbody * r0, float s0): Primitive(r0)
{
  distance_center_to_face = s0;
}

float Box::get_distance()
{
  return distance_center_to_face;
}
  


