#ifndef _FORCE_REGISTER_
#define _FORCE_REGISTER_

#include <vector>

#include "rigidbody.hpp"
#include "rigidbody_force_generator.hpp"

class ForceRegister {
public:

  struct ForceRecording {
    Rigidbody *rigidbody;
    RigidbodyForceGenerator *fg;
  };

  typedef std::vector<struct ForceRecording> records;
  records forces;


  void add(Rigidbody *rigidbody, RigidbodyForceGenerator *fg);
  void erase(Rigidbody *rigidbody, RigidbodyForceGenerator *fg);
  int count();

  records get_force_register();
};

#endif
