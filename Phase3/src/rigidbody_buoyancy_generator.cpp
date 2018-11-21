#include "vector3D.hpp"

#include "rigidbody_buoyancy_generator.hpp"


RigidbodyBuoyancyGenerator::RigidbodyBuoyancyGenerator(float max_deepness, float object_volume, float water_height, float density){
  this->max_deepness = max_deepness;
  this->object_volume = object_volume;
  this->water_height = water_height;
  this->density = density;
}

void RigidbodyBuoyancyGenerator::update_force(Rigidbody * rigidbody, float period){

  float s = 1; //a rigidbody doesn't have a size, it is just a arbitrary value to make it works!
  float subversion = (rigidbody->get_position().get_y() - this->water_height - s) / (2 * s);
  float value;
  Vector3D force;

  if (subversion >= 0){
    value = 0;
  }
  else if (subversion <= -1){
    value = this->object_volume * this->density;
  }
  else {
    value = this->object_volume * this->density * subversion;
  }

  force = Vector3D(0, value, 0);
  rigidbody->add_force_at_point(force,rigidbody->get_position());
}
