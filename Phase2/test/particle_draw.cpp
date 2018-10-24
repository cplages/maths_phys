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

// physic handler
GameWorld *game;

//particle color
float RGB[MAX_PARTICLES][3];

float current_time;

//list of particles.
std::vector<Particle*> active_particles;

// apply physic to the game
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

  glColor3f(1., 1., 1.);
  //floor display
  glBegin(GL_POLYGON);

  glVertex3f(FLOOR_WIDTH_MIN, FLOOR_HEIGHT - 2, 0.0);
  glVertex3f(FLOOR_WIDTH_MIN, FLOOR_HEIGHT, 0.0);
  glVertex3f(FLOOR_WIDTH_MAX, FLOOR_HEIGHT, 0.0);
  glVertex3f(FLOOR_WIDTH_MAX, FLOOR_HEIGHT - 2, 0.0);

  glEnd();
  
  int i = 0;
  //draw particles
  for(vector<Particle *>::iterator it = active_particles.begin(); it != active_particles.end(); ++it)
    {
      Vector3D p = (*it)->get_position();
      
      glPushMatrix();
      
      glColor3f(RGB[i][0],RGB[i][1],RGB[i][2]);

      //draw circles
      glBegin(GL_POLYGON);

      for(double j = 0; j < 2 * M_PI; j+= M_PI/(PARTICLE_POINT_NUMBER / 2))
      {
        glVertex3f((cos(j) * PARTICLE_RADIUS) + p.get_x(), (sin(j) * PARTICLE_RADIUS) + p.get_y(), 0.0);
      }
      
      glEnd();
      
      glPopMatrix();
      
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
// Catch the input of the player, move the player
void handler_event(unsigned char key, int x, int y) {
  Particle * main_particle = active_particles.back();
  
  Vector3D new_velocity = main_particle->get_velocity();
  
  switch(key) {
    case 'z':
      new_velocity += Vector3D(0, PARTICLE_RADIUS, 0);
      main_particle->set_velocity(new_velocity);
      break;
      
    case 'q':
      new_velocity += Vector3D(-PARTICLE_RADIUS, 0, 0);
      main_particle->set_velocity(new_velocity);
      break;
      
    case 's':
      new_velocity += Vector3D(0, -PARTICLE_RADIUS, 0);
      main_particle->set_velocity(new_velocity);
      break;
      
    case 'd':
      new_velocity += Vector3D(PARTICLE_RADIUS, 0, 0);
      main_particle->set_velocity(new_velocity);
      break;
      
    default:
      break;
  }
  
  glutPostRedisplay();
}

// Print basic instructions for the player
void display_init(){
  printf("Blob group application \n");
  printf("tape, z, s, q, d, to move the white blob, the rest will follow! \n");
}

//init opengl functions and game parameters.
int main(int argc, char** argv)
{
  current_time = 0;
  
  // Total number of particles
  int n = 10;

  //initiate game physics.
  game = new GameWorld(n, PARTICLE_RADIUS);
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
