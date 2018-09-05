#include <stdio.h>
#include <float.h>
#include <math.h>

#include "particule.hpp"

Particule::Particule() {
  this->position = Vector3D();
  this->velocity = Vector3D();
  this->acceleration = Vector3D();
  this->inverse_mass = 0;
  this->gravity = Vector3D();
  this->dumping = 0;
}


Particule::Particule(Vector3D p0, Vector3D v0, float m0, float g0, float d0){
  this->position = p0;
  this->velocity = v0;
  if (m0 == 0){
    printf("Masse nulle impossible\n");
    this->inverse_mass = FLT_MAX;
  }
  else {
    this->inverse_mass = 1 / m0;
  }
  this->gravity = Vector3D(0,0,-g0);
  this->acceleration = this->gravity;
  this->dumping = d0;
}

float Particule::get_inverse_mass(){
  return inverse_mass;
}


void Particule::set_mass(float m0){
  if (m0 == 0){
    printf("Masse nulle impossible\n");
    this->inverse_mass = FLT_MAX;
  }
  else {
    this->inverse_mass = 1 / m0;
  }
} 


void Particule::integer(float t){
  //Update position
  Vector3D vt = this->velocity.mult_scal(t);
  Vector3D new_p = this->position.add(&vt);
  this->position = new_p;
  
  //Update velocity
  Vector3D at = this->acceleration.mult_scal(t);
  Vector3D new_v = this->velocity.mult_scal(pow(this->dumping, t)).add(&at);
  this->velocity = new_v;
}

void Particule::display(){
  printf("Particule : ");
  printf("\t position = ");
  this->position.display();
  printf("\t velocity = ");
  this->velocity.display();
  printf("\n");
}

Particule::~Particule(){
}


