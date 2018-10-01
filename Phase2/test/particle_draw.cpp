#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "../src/vector3D.hpp"

#include "../src/particle.hpp"
#include "../src/particle_force_generator.hpp"
#include "../src/particle_gravity_generator.hpp"

#include "../src/force_register.hpp"

using namespace std;

/* GLUT Particle Launcher animations

- 4 differents particles availables

*/

int WINDOW_SIZE = 1600;
int WINDOW_POSITION_X = 100;
int WINDOW_POSITION_Y = 100;

int CAMERA_EYE_X = 150;
int CAMERA_EYE_Y = -20;
int CAMERA_EYE_Z = 250;
int CAMERA_VIEW_X = 150;
int CAMERA_VIEW_Y = -20;
int CAMERA_VIEW_Z = 0;
int CAMERA_UP_X = 0;
int CAMERA_UP_Y = 1;
int CAMERA_UP_Z = 0;

ForceRegister *  particles_and_forces;

vector<ParticleForceGenerator *> force_generator_instances;

vector<Particle> particle_types;
vector<Particle> particle_instances;

float animation_time = 10.0f;
float current_time;
float interval = 1.0/30.0;

Vector3D old_p;

bool launch = false;

/* Physics Region */
void init_particles_types() {
  int size = 4;
  Particle gun_bullet = Particle(Vector3D(), Vector3D(35,0,0), Vector3D(0, 0, 0) , 2);
  Particle fire_ball = Particle(Vector3D(), Vector3D(50,0,0), Vector3D(0, 0, 0) , 2);
  Particle laser = Particle(Vector3D(), Vector3D(100,0,0), Vector3D(0, 0, 0), 2);
  Particle canon = Particle(Vector3D(), Vector3D(70,0,0), Vector3D(0, 0, 0), 2);

  ParticleGravityGenerator *gravity = new ParticleGravityGenerator(Vector3D(0, -10, 0));

  force_generator_instances.push_back(gravity);

  particle_types.push_back(gun_bullet);
  particle_types.push_back(fire_ball);
  particle_types.push_back(laser);
  particle_types.push_back(canon);
  
  particle_instances.push_back(particle_types[0]);

  particles_and_forces->add(&(particle_instances[0]), force_generator_instances[0]);
}


void call_all_force_generator()
{
  ForceRegister::records forces = particles_and_forces->get_force_register();

  for(ForceRegister::records::iterator it = forces.begin(); it != forces.end(); ++it)
    {
      ParticleForceGenerator* current_force = it->fg;
      Particle * current_particle = it->particle;
      current_force->update_force(current_particle, interval);
    }
}

// Integration of the particle during the animation
void idle_func(void) {
  clock_t start_time = clock();
  if(current_time < animation_time && launch) {
    call_all_force_generator();
    //give to integrate the time between two frame
    for(vector<Particle>::iterator it = particle_instances.begin(); it != particle_instances.end(); ++it)
      {
	it->integrate(interval);
      }

    current_time += interval;
    float remaining_time = interval - (clock() - start_time) / CLOCKS_PER_SEC;
    if(remaining_time > 0) {
      //multiply by 1000 due to sleep function taking millisecond in argument.
      usleep(remaining_time * 1000);
    }
  }
  else if( current_time >= animation_time  && launch) {
    launch = false;
    current_time = 0.0f;
    old_p = Vector3D();
    glPopMatrix();
    printf("End of animation !\n");
  }
  glutPostRedisplay();
}


/* Display Region */
// Display function called every frame
void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );

  for(vector<Particle>::iterator it = particle_instances.begin(); it != particle_instances.end(); ++it)
    {
      Vector3D p = it->get_position();

      glTranslated(p.get_x() - old_p.get_x(), p.get_y() - old_p.get_y(), p.get_z() - old_p.get_z());
      glutSolidSphere(1,30,30);

      old_p = p;
    }
  glutSwapBuffers();
  glutPostRedisplay();
}

// Reshape the window size if necessary
void reshape(int width, int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
		 45,
		 float(width)/float(height),
		 0.1,
		 250
		 );
  glMatrixMode(GL_MODELVIEW);
}

// Initialisation of the 4 types of particles


/* Event Region*/
// Catch the input of the player
void handler_event(unsigned char key, int x, int y) {
  if(launch == false) {
    switch(key) {
    case '1':
      particle_instances[0] = particle_types[0];
      glColor3f(1.0,1.0,1.0);
      break;
    case '2':
      particle_instances[0] = particle_types[1];
      glColor3f(1.0,0.0,0.0);
      break;
    case '3':
      particle_instances[0] = particle_types[2];
      glColor3f(0.0,1.0,0.0);
      break;
    case '4':
      particle_instances[0] = particle_types[3];
      glColor3f(0.0,0.0,1.0);
      break;
    case 'l':
      printf("particle launched ! \n");
      launch = true;
      glPushMatrix();
      break;
    default:
      break;
    }
  }
  glutPostRedisplay();
}

// Print basic instructions for the player
void display_init(){
  printf("Welcome to the particle Launcher !\n");
  printf("You have 4 particles availables : gun bullet, fire ball, laser and canon. Push 1 to 4 respectively to choose one.\n");
  printf("Then push `l` to launch the particle.\n");
  printf("When the animation is over, you can start again by choosing a particle and launching it.\n");
}

int main(int argc, char** argv)
{
  current_time = 0.0f;
  old_p = Vector3D();

  particles_and_forces = new ForceRegister();

  init_particles_types();

  display_init();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow("particle launcher");
  glutKeyboardFunc(handler_event);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle_func);
  gluLookAt(CAMERA_EYE_X, CAMERA_EYE_Y, CAMERA_EYE_Z, CAMERA_VIEW_X, CAMERA_VIEW_Y, CAMERA_VIEW_Z, CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);

  glutMainLoop();
  return 0;
}
