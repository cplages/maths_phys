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
