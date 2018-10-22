#include <vector>

#include "constant.hpp"
#include "particle_contact_resolver.hpp"

using namespace std;

ParticleContactResolver::ParticleContactResolver(vector<ParticleContact *> collisions) : collisions(collisions)
{
  max_iteration = 2 * collisions.size();
}

void ParticleContactResolver::resolve_contacts()
{
  int size = collisions.size();

  bool stop_iterate = false;
  int i = 0;

  //resolve
  while(i < max_iteration/*size*/ && !stop_iterate)
    {
      float min_vs = collisions[0]->compute_vs();
      ParticleContact* tmp_contact = collisions[0];
      for(int j = 1; j < size; ++j)
	     {
    	  float current_vs = collisions[j]->compute_vs();
    	  if(min_vs > current_vs)
    	   {
    	      min_vs = current_vs;
    	      tmp_contact = collisions[j];
    	   }
       }
       if(min_vs >= 0)
    	{
    	  stop_iterate = true;
    	}
      else
  	 {
  	  tmp_contact->resolve(FRAME_INTERVAL);
    }

    //  collisions[i]->resolve(FRAME_INTERVAL);
      ++i;
    }

}
