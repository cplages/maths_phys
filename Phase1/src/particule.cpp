#include <stdio.h>
#include <float.h>
#include <math.h>

#include "particule.hpp"

// Basic constructor
Particule::Particule() {
  this->position = Vector3D();
  this->velocity = Vector3D();
  this->acceleration = Vector3D();
  this->inverse_mass = 0;
  this->gravity = Vector3D();
  this->dumping = 0;
}

// Basic constructor with variables
Particule::Particule(Vector3D p0, Vector3D v0, float m0, float g0, float d0){
  this->position = p0;
  this->velocity = v0;
  //Checking if the mass is not null
  if (m0 == 0){
    printf("Masse nulle impossible\n");
    this->inverse_mass = FLT_MAX;
  }
  else {
    this->inverse_mass = 1 / m0;
  }
  this->gravity = Vector3D(0,-g0,0);
  this->acceleration = this->gravity;
  this->dumping = d0;
}

//Getters and setters
Vector3D Particule::get_position() {
  return this->position;
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

// Update the position and velocity of the particule
void Particule::integrate(float t){
  //Update position
  //Vector3D vt = this->velocity.mult_scal(t);
  //Vector3D new_p = this->position.add(&vt);
  Vector3D vt = this->velocity * t;
  Vector3D new_p = this->position + vt;

  this->position = new_p;

  //Update velocity
  //Vector3D at = this->acceleration.mult_scal(t);
  //Vector3D new_v = this->velocity.mult_scal(pow(this->dumping, t)).add(&at);
  Vector3D at = this->acceleration * t;
  Vector3D new_v = this->velocity * pow(this->dumping, t) + at;

  this->velocity = new_v;
}

// Print some attributes of the particule
void Particule::display(){
  printf("Particule : ");
  printf("\t position = ");
  this->position.display();
  printf("\t velocity = ");
  this->velocity.display();
  printf("\n");
}

// Equal operator
Particule& Particule::operator =(Particule const& p) {
  this->position = p.position;
  this->velocity = p.velocity;
  this->acceleration = p.acceleration;
  this->inverse_mass = p.inverse_mass;
  this->gravity = p.gravity;
  this->dumping = p.dumping;
  return *this;
}

// Destructor
Particule::~Particule(){
}
