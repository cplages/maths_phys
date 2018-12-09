#include "contact.hpp"
#include "collision_data.hpp"
#include <stdio.h>


CollisionData::CollisionData(){
  remaining_contacts = 0;
  contacts = NULL;
}

CollisionData::CollisionData(int contacts_max){
  remaining_contacts = contacts_max;
  contacts = new Contact[remaining_contacts];
  current_size = 0;
}

void CollisionData::add_contact(Contact c){
  if (remaining_contacts != 0){
    contacts[current_size] = c;
    current_size ++;
    remaining_contacts--;
  }
  else {
    printf("Max contacts reached\n");
  }
}


int CollisionData::get_current_size() {
  return current_size;
}

Contact CollisionData::get_contact() {
  return contacts[0];
}

//Only for contacts between plane and box
void generate_contacts(Box * box, Plane * plane, CollisionData * data){
  Vector3D * box_vertices = box->get_vertices();

  for (int i = 0; i<8; i++){
      //check box vertex below plane
      float distance = plane->get_distance_from_point(box_vertices[i]);
      if (distance <= 0){
        float penetration = -distance;
        //contact point between vertex and the plane
        Vector3D contact_point = box_vertices[i] + plane->get_normal() * (penetration / 2);
        Contact c = Contact(contact_point, plane->get_normal(), penetration);
        data->add_contact(c);
      }
  }

}
