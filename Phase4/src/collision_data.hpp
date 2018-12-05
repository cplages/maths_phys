#ifndef _CONTACT_DATA_H_
#define _CONTACT_DATA_H_

#include "contact.hpp"
#include "primitive.hpp"
#include "box.hpp"
#include "plane.hpp"

class CollisionData {

private:
  Contact * contacts;
  int remaining_contacts;
  int current_size;

public:

  CollisionData();
  CollisionData(int contacts_max);

  void add_contact(Contact c);


};

void generate_contacts(Box * box, Plane * plane, CollisionData * data);

#endif // _CONTACT_DATA_H_
