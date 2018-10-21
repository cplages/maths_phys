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

#include "game_world.hpp"


using namespace std;

/* Graphic part of the game */

int WINDOW_SIZE = 1600;
int WINDOW_POSITION_X = 100;
int WINDOW_POSITION_Y = 100;

int CAMERA_EYE_X = 0;
int CAMERA_EYE_Y = 0;
int CAMERA_EYE_Z = 100;
int CAMERA_VIEW_X = 0;
int CAMERA_VIEW_Y = 0;
int CAMERA_VIEW_Z = 0;
int CAMERA_UP_X = 0;
int CAMERA_UP_Y = 1;
int CAMERA_UP_Z = 0;


float current_time;
std::vector<Particle*> active_particles;
GameWorld *game;

std::vector<Vector3D> old_p;


void update_physic(){
  game->execute(&current_time);
}

// Display function called every frame
void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );

  int i = 0;
  for(vector<Particle *>::iterator it = active_particles.begin(); it != active_particles.end(); ++it)
    {
      Vector3D p = (*it)->get_position();
      glTranslated(p.get_x() - old_p[i].get_x(), p.get_y() - old_p[i].get_y(), p.get_z() - old_p[i].get_z());
      glutSolidSphere(1,30,30);

      old_p[i] = p;
      i++;
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



/* Event Region*/
// Catch the input of the player
void handler_event(unsigned char key, int x, int y) {
  /*if(launch == false) {
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
  glutPostRedisplay();*/
}

// Print basic instructions for the player
void display_init(){
  printf("BLABLA\n");
}

int main(int argc, char** argv)
{
  current_time = 0;

  int n = 2;
  for (int i=0; i<n;  i++){
    old_p.push_back(Vector3D());
  }

  game = new GameWorld(n);
  active_particles = game->get_active_particles();

  display_init();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow("particle launcher");
  glutKeyboardFunc(handler_event);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_physic);
  gluLookAt(CAMERA_EYE_X, CAMERA_EYE_Y, CAMERA_EYE_Z, CAMERA_VIEW_X, CAMERA_VIEW_Y, CAMERA_VIEW_Z, CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);

  glutMainLoop();
  return 0;
}
