#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector3D.hpp"

Vector3D::Vector3D() {
  this->x  = 0;
  this->y  = 0;
  this->z  = 0;
}
  
Vector3D::Vector3D(float x0, float y0, float z0) {
  this->x  = x0;
  this->y  = y0;
  this->z  = z0;
}

float Vector3D::get_x() {
  return this->x;
}

float Vector3D::get_y() {
  return this->y;
}

float Vector3D::get_z() {
  return this->z;
}

Vector3D Vector3D::add(Vector3D const *v) const{
  float new_x = this->x + v->x;
  float new_y = this->y + v->y;
  float new_z = this->z + v->z;
  return Vector3D(new_x, new_y, new_z);
}

Vector3D Vector3D::mult_scal(float k) const{
  float new_x = this->x * k;
  float new_y = this->y * k;
  float new_z = this->z * k;
  return Vector3D(new_x, new_y, new_z);
}

Vector3D Vector3D::composant_product(Vector3D *v) const{
  float new_x = this->x * v->x;
  float new_y = this->y * v->y;
  float new_z = this->z * v->z;
  return Vector3D(new_x, new_y, new_z);
}

float Vector3D::dot_product(Vector3D const *v) const {
  return (this->x * v->x) + (this->y * v->y) + (this->z * v->z);
}

Vector3D Vector3D::cross_product(Vector3D *v) const{
  float new_x = (this->y * v->z) - (this->z * v->y);
  float new_y = (this->z * v->x) - (this->x * v->z);
  float new_z = (this->x * v->y) - (this->y * v->x);
  return Vector3D(new_x, new_y, new_z);
}

float Vector3D::norm() const{
  return sqrt(this->dot_product(this));
}

Vector3D Vector3D::proj( Vector3D *v) const {
  float k = this->dot_product(v) / pow(v->norm(),2);
  return v->mult_scal(k);
}

float Vector3D::distance(Vector3D *v) const {
  float distance_x = this->x - v->x;
  float distance_y = this->y - v->y;
  float distance_z = this->z - v->z;
  return sqrt(pow(distance_x,2) + pow(distance_y,2) + pow(distance_z,2));
}

float Vector3D::triple_product(Vector3D *v,Vector3D *w) const {
  Vector3D result_cross_product = v->cross_product(w);
  return this->dot_product(&result_cross_product);
}

void Vector3D::display(){
  printf("(%f, %f, %f) ", this->x, this->y, this->z);
}

Vector3D::~Vector3D(){
}

bool Vector3D::operator ==(Vector3D const& v) {
  if( this->x == v.x && this->y == v.y && this->z == v.z) {
    return true;
  }
  return false;
}

bool Vector3D::operator !=(Vector3D const& v) {
  if( this->x == v.x && this->y == v.y && this->z == v.z) {
    return false;
  }
  return true;
}


Vector3D& Vector3D::operator =(const Vector3D& v){
  this->x = v.x;
  this->y = v.y;
  this->z = v.z;
  return *this;
}

Vector3D operator +(Vector3D const& v, Vector3D const& w) {
  Vector3D result = v.add(&w);
  return result;
}

Vector3D operator *(Vector3D const& v, float const& k) {
  return v.mult_scal(k);

}

