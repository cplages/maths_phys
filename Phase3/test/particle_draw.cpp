#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>

#include "../src/constant.hpp"
#include "../src/vector3D.hpp"
#include "../src/rigidbody.hpp"
#include "../src/matrix33.hpp"
#include "../src/matrix34.hpp"
#include "../src/quaternion.hpp"
#include "../src/rigidbody_force_generator.hpp"
#include "../src/rigidbody_gravity_generator.hpp"
#include "../src/force_register.hpp"

#include "game_world.hpp"

using namespace std;

// physic handler
GameWorld *game;

//rigidbody color
float RGB[MAX_PARTICLES][3];

float current_time;



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

  Vector3D p = game->get_rigidbody()->get_position();
  p.display();
  int radius = 2;
  Vector3D vertice1 = Vector3D(-radius,-radius,0);
  Vector3D vertice2 = Vector3D(-radius,radius,0);
  Vector3D vertice3 = Vector3D(radius,radius,0);
  Vector3D vertice4 = Vector3D(radius,-radius,0);

  vertice1 = game->get_rigidbody()->local_to_world(vertice1);
  vertice2 = game->get_rigidbody()->local_to_world(vertice2);
  vertice3 = game->get_rigidbody()->local_to_world(vertice3);
  vertice4 = game->get_rigidbody()->local_to_world(vertice4);
  //floor display
  glBegin(GL_POLYGON);

  glVertex3f(vertice1.get_x(), vertice1.get_y(), vertice1.get_z());
  glVertex3f(vertice2.get_x(), vertice2.get_y(), vertice2.get_z());
  glVertex3f(vertice3.get_x(), vertice3.get_y(), vertice3.get_z());
  glVertex3f(vertice4.get_x(), vertice4.get_y(), vertice4.get_z());

  glEnd();

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



/*
// Catch the input of the player, move the player
void handler_event(unsigned char key, int x, int y) {
  Vector3D new_velocity = main_rigidbody->get_velocity();

  switch(key) {
    case 'z':
      new_velocity += Vector3D(0, PARTICLE_RADIUS, 0);
      main_rigidbody->set_velocity(new_velocity);
      break;

    case 'q':
      new_velocity += Vector3D(-PARTICLE_RADIUS, 0, 0);
      main_rigidbody->set_velocity(new_velocity);
      break;

    case 's':
      new_velocity += Vector3D(0, -PARTICLE_RADIUS, 0);
      main_rigidbody->set_velocity(new_velocity);
      break;

    case 'd':
      new_velocity += Vector3D(PARTICLE_RADIUS, 0, 0);
      main_rigidbody->set_velocity(new_velocity);
      break;

    default:
      break;
  }

  glutPostRedisplay();
}
*/
// Print basic instructions for the player
void display_init(){
  printf("Phase 3 : Rotation on rigidbodies \n");
}

//init opengl functions and game parameters.
int main(int argc, char** argv)
{
  current_time = 0;


  //initiate game physics.
  game = new GameWorld();

  display_init();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow("Rigidbody animations");
  //glutKeyboardFunc(handler_event);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_physic);
  gluLookAt(CAMERA_EYE_X, CAMERA_EYE_Y, CAMERA_EYE_Z, CAMERA_VIEW_X, CAMERA_VIEW_Y, CAMERA_VIEW_Z, CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);

  glutMainLoop();
  return 0;
}
