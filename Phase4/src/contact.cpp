#include <stdio.h>

#include "vector3D.hpp"

#include "contact.hpp"

Contact::Contact(){
  contact_point = Vector3D();
  contact_normal = Vector3D();
  penetration = 0;
}

Contact::Contact(Vector3D cp, Vector3D cn, float p){
  contact_point = cp;
  contact_normal = cn;
  penetration = p;
}

Vector3D Contact::get_normal() {
  return contact_normal;
}

void Contact::display() {
  printf("DISPLAY CONTACT: \n");
  printf("contact_point: ");
  contact_point.display();
  printf("contact_normal: ");
  contact_normal.display();
  printf("penetration: %f\n", penetration);
  printf("end display \n \n");
}
