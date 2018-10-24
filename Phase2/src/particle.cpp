#include <stdio.h>
#include <float.h>
#include <math.h>

#include "particle.hpp"

// Basic constructor
Particle::Particle() {
  this->position = Vector3D();
  this->velocity = Vector3D();
  this->acceleration = Vector3D();
  this->inverse_mass = 0;
  this->accum_force = Vector3D();
  this->radius = 0;
}

// Basic constructor with variables
Particle::Particle(Vector3D p0, Vector3D v0, Vector3D a0, float m0, float r){
  this->position = p0;
  this->velocity = v0;
  this->acceleration = a0;
  //Checking if the mass is not null
  if (m0 == 0){
    printf("Masse nulle impossible\n");
    this->inverse_mass = FLT_MAX;
  }
  else {
    this->inverse_mass = 1 / m0;
  }

  this->accum_force = Vector3D();

  this->radius = r;
}

//Getters and setters
Vector3D Particle::get_position() {
  return this->position;
}

void Particle::set_position(Vector3D p0) {
  this->position = p0;
}

Vector3D Particle::get_velocity() {
  return this->velocity;
}

void Particle::set_velocity(Vector3D v0) {
  this->velocity = v0;
}

float Particle::get_inverse_mass(){
  return inverse_mass;
}

float Particle::get_radius(){
  return radius;
}

void Particle::set_mass(float m0){
  if (m0 == 0){
    printf("Masse nulle impossible\n");
    this->inverse_mass = FLT_MAX;
  }
  else {
    this->inverse_mass = 1 / m0;
  }
}

// Update the position and velocity of the particle
void Particle::integrate(float t){
  this->acceleration = this->accum_force * this->inverse_mass;

  //Update position
  Vector3D vt = this->velocity * t;
  Vector3D new_p = this->position + vt;
  this->position = new_p;

  //Update velocity
  Vector3D at = this->acceleration * t;
  Vector3D new_v = this->velocity + at;
  this->velocity = new_v;

  this->clear_accum();
}

// Add new force to the resulting force
void Particle::add_force(const Vector3D &force) {
  accum_force += force;
}

// Reset resulting force
void Particle::clear_accum() {
  accum_force = Vector3D();
}

// Print some attributes of the particle
void Particle::display(){
  printf("Particle : ");
  printf("\t position = ");
  this->position.display();
  printf("\t velocity = ");
  this->velocity.display();
  printf("\n");
}

// Penetration correspond to the difference between the two radius and the particle center distances
float Particle::get_interpenetration_with(Particle * p){
  Vector3D other_center = p->position;
  return (this->radius + p->radius) - (this->position.distance(&other_center));
}

// Affect operator
Particle& Particle::operator =(Particle const& p) {
  this->position = p.position;
  this->velocity = p.velocity;
  this->acceleration = p.acceleration;
  this->inverse_mass = p.inverse_mass;
  return *this;
}


// Destructor
Particle::~Particle(){
}
