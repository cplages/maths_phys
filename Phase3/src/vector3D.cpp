#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector3D.hpp"

// Basic constructor
Vector3D::Vector3D() {
  this->x  = 0;
  this->y  = 0;
  this->z  = 0;
}

// Basic constructor with variables
Vector3D::Vector3D(float x0, float y0, float z0) {
  this->x  = x0;
  this->y  = y0;
  this->z  = z0;
}

// Getters
float Vector3D::get_x() const{
  return this->x;
}

float Vector3D::get_y() const{
  return this->y;
}

float Vector3D::get_z() const{
  return this->z;
}

float Vector3D::get_by_index(int i) const{
  switch (i) {
    case 0:
      return this->x;
      break;
    case 1:
      return this->y;
      break;
    case 2:
      return this->z;
      break;
    default:
      return 0;
      break;
  }
}


void Vector3D::set_by_index(int i, float value){
  switch (i) {
    case 0:
      this->x = value;
      break;
    case 1:
      this->y = value;
      break;
    case 2:
      this->z = value;
      break;
    default:
      break;
  }
}

// Addition of the vector with another
Vector3D Vector3D::add(Vector3D const *v) const{
  float new_x = this->x + v->x;
  float new_y = this->y + v->y;
  float new_z = this->z + v->z;
  return Vector3D(new_x, new_y, new_z);
}

// Scalar multiplication of the vector and a float
Vector3D Vector3D::mult_scal(float k) const{
  float new_x = this->x * k;
  float new_y = this->y * k;
  float new_z = this->z * k;
  return Vector3D(new_x, new_y, new_z);
}

// Composant product of the vector with another
Vector3D Vector3D::composant_product(Vector3D *v) const{
  float new_x = this->x * v->x;
  float new_y = this->y * v->y;
  float new_z = this->z * v->z;
  return Vector3D(new_x, new_y, new_z);
}

/// Dot product of the vector with another
float Vector3D::dot_product(Vector3D const *v) const {
  return (this->x * v->x) + (this->y * v->y) + (this->z * v->z);
}

/// Cross product of the vector with another
Vector3D Vector3D::cross_product(Vector3D *v) const{
  float new_x = (this->y * v->z) - (this->z * v->y);
  float new_y = (this->z * v->x) - (this->x * v->z);
  float new_z = (this->x * v->y) - (this->y * v->x);
  return Vector3D(new_x, new_y, new_z);
}

// Norm of the vector
float Vector3D::norm() const{
  return sqrt(this->dot_product(this));
}

// Projection of the vector on another
Vector3D Vector3D::proj( Vector3D *v) const {
  float k = this->dot_product(v) / pow(v->norm(),2);
  return v->mult_scal(k);
}

// Distance between the vector and another
float Vector3D::distance(Vector3D *v) const {
  float distance_x = this->x - v->x;
  float distance_y = this->y - v->y;
  float distance_z = this->z - v->z;
  return sqrt(pow(distance_x,2) + pow(distance_y,2) + pow(distance_z,2));
}

// Triple product between the vector and two others
float Vector3D::triple_product(Vector3D *v,Vector3D *w) const {
  Vector3D result_cross_product = v->cross_product(w);
  return this->dot_product(&result_cross_product);
}

// Print the attributes of the vector
void Vector3D::display(){
  printf("(%f, %f, %f) \n", this->x, this->y, this->z);
}

// Destructor
Vector3D::~Vector3D(){
}

// Equal operator
bool Vector3D::operator ==(Vector3D const& v) {
  if( this->x == v.x && this->y == v.y && this->z == v.z) {
    return true;
  }
  return false;
}

// Not Equal operator
bool Vector3D::operator !=(Vector3D const& v) {
  if( this->x == v.x && this->y == v.y && this->z == v.z) {
    return false;
  }
  return true;
}

// Affectation operator
Vector3D& Vector3D::operator =(const Vector3D& v){
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  return *this;
}

// Add the vector v to itself
Vector3D& Vector3D::operator +=(const Vector3D& v){
  this->x += v.x;
  this->y += v.y;
  this->z += v.z;
  return *this;
}

// Addition operator
Vector3D operator +(Vector3D const& v, Vector3D const& w) {
  Vector3D result = v.add(&w);
  return result;
}

// Soustraction operator
Vector3D operator -(Vector3D const& v, Vector3D const& w) {
  float new_x = v.get_x() - w.get_x();
  float new_y = v.get_y() - w.get_y();
  float new_z = v.get_z() - w.get_z();
  return Vector3D(new_x, new_y, new_z);
}

// Scalar multiplication operator
Vector3D operator *(Vector3D const& v, float const& k) {
  return v.mult_scal(k);

}
