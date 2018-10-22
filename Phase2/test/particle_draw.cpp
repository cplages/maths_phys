#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "../src/constant.hpp"
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
float radius;
std::vector<Particle*> active_particles;
GameWorld *game;
float RGB[MAX_PARTICLES][3];

std::vector<Vector3D> old_p;


void update_physic(){
  game->execute(&current_time);
  glutPostRedisplay();
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
      glPushMatrix();
      glColor3f(RGB[i][0],RGB[i][1],RGB[i][2]);
      //glTranslated(p.get_x() - old_p[i].get_x(), p.get_y() - old_p[i].get_y(), p.get_z() - old_p[i].get_z());
      //glutSolidSphere(radius,30,30);
      glBegin(GL_POLYGON);
      int point_number = 6;
      for(double j = 0; j < 2 * 3.14; j+= 3.14/point_number)
      {
        glVertex3f((cos(j) * radius) + p.get_x(), (sin(j) * radius) + p.get_y(), 0.0);
      }
      glEnd();
      glPopMatrix();

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
  Particle * main_particle = active_particles.back();
  Vector3D new_position = main_particle->get_position();
  switch(key) {
    case 'z':
      new_position += Vector3D(0,radius,0);
      main_particle->set_position(new_position);
      break;
    case 'q':
      new_position += Vector3D(-radius,0,0);
      main_particle->set_position(new_position);
      break;
    case 's':
      new_position += Vector3D(0,-radius,0);
      main_particle->set_position(new_position);
      break;
    case 'd':
      new_position += Vector3D(radius,0,0);
      main_particle->set_position(new_position);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

// Print basic instructions for the player
void display_init(){
  printf("BLABLA\n");
}

int main(int argc, char** argv)
{
  current_time = 0;
  radius = 1.;
  // Total number of particles
  int n = 10;
  for (int i=0; i<n;  i++){
    old_p.push_back(Vector3D());
  }

  game = new GameWorld(n, radius);
  active_particles = game->get_active_particles();

  // Color particles init
  srand(time(NULL));
  for (int k = 0; k<n-1; k++){
    RGB[k][0] = ((float) rand()) / ((float) RAND_MAX); //to have a random float betwen [0,1]
    RGB[k][1] = ((float) rand()) / ((float) RAND_MAX);
    RGB[k][2] = ((float) rand()) / ((float) RAND_MAX);
  }
  // main particle in white
  RGB[n-1][0] = 1;
  RGB[n-1][1] = 1;
  RGB[n-1][2] = 1;

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
