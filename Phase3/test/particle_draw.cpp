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
  float width = 0.5;
  float height = 1;
  float deepness = 1;
  Vector3D vertices[8];
  vertices[0] = Vector3D(-width, -height, -deepness);
  vertices[1] = Vector3D(-width, height, -deepness);
  vertices[2] = Vector3D(width, height, -deepness);
  vertices[3] = Vector3D(width, -height, -deepness);
  vertices[4] = Vector3D(width, -height, deepness);
  vertices[5] = Vector3D(width, height, deepness);
  vertices[6] = Vector3D(-width, height, deepness);
  vertices[7] = Vector3D(-width, -height, deepness);

  for(int i =0 ; i < 8; ++i)
  {
    vertices[i] = game->get_rigidbody()->local_to_world(vertices[i]);
  }

  //floor display
  glBegin(GL_POLYGON);

  for(int i =0 ; i < 8; ++i)
  {
    glVertex3f(vertices[i].get_x(), vertices[i].get_y(), vertices[i].get_z());
  }

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
  printf("gravity value! : %f\n", GRAVITY_VALUE);
  glutMainLoop();
  return 0;
}
