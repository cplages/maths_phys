#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
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

bool exercice_1 = true;

// physic handler
GameWorld *game;


float current_time;



// apply physic to the game
void update_physic(){
  game->execute(&current_time);
  glutPostRedisplay();
}


void create_rectangle(Rigidbody *object, Vector3D (*vertices)[VERTEX_PER_SIDE] ,float width, float height, float deepness)
{

  //back side
  vertices[0][0] = Vector3D(-width, -height, -deepness);
  vertices[0][1] = Vector3D(width, -height, -deepness);
  vertices[0][2] = Vector3D(width, height, -deepness);
  vertices[0][3] = Vector3D(-width, height, -deepness);

  //bottom side
  vertices[1][0] = Vector3D(-width, -height, -deepness);
  vertices[1][1] = Vector3D(width, -height, -deepness);
  vertices[1][2] = Vector3D(width, -height, deepness);
  vertices[1][3] = Vector3D(-width, -height, deepness);
  
  //left side
  vertices[2][0] = Vector3D(-width, -height, -deepness);
  vertices[2][1] = Vector3D(-width, height, -deepness);
  vertices[2][2] = Vector3D(-width, height, deepness);
  vertices[2][3] = Vector3D(-width, -height, deepness);

  //right side
  vertices[3][0] = Vector3D(width, -height, -deepness);
  vertices[3][1] = Vector3D(width, height, -deepness);
  vertices[3][2] = Vector3D(width, height, deepness);
  vertices[3][3] = Vector3D(width, -height, deepness);
  
  //up side
  vertices[4][0] = Vector3D(-width, height, -deepness);
  vertices[4][1] = Vector3D(width, height, -deepness);
  vertices[4][2] = Vector3D(width, height, deepness);
  vertices[4][3] = Vector3D(-width, height, deepness);

  //front side
  vertices[5][0] = Vector3D(-width, -height, deepness);
  vertices[5][1] = Vector3D(width, -height, deepness);
  vertices[5][2] = Vector3D(width, height, deepness);
  vertices[5][3] = Vector3D(-width, height, deepness);

  for(int i = 0; i < SIDE_NUMBER; ++i) {    
    for(int j = 0 ; j < VERTEX_PER_SIDE; ++j) {
      vertices[i][j] = object->local_to_world(vertices[i][j]);
    }
  }
}

// Display function called every frame
void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );
  float width = 0.5;
  float height = 1;
  float deepness = 1;
  if(exercice_1) {
    Vector3D vertices[SIDE_NUMBER][VERTEX_PER_SIDE];    
    float RGB[3] = {1,0,0};
    
    create_rectangle(game->get_main_rigidbody(), vertices, width, height, deepness); 

    
    for(int i = 0; i < SIDE_NUMBER; ++i)
      {
	glBegin(GL_POLYGON);
	glColor3f(RGB[0], RGB[1], RGB[2]);
	for(int j = 0 ; j < VERTEX_PER_SIDE; ++j)
	  {
	    glVertex3f(vertices[i][j].get_x(), vertices[i][j].get_y(), vertices[i][j].get_z());
	  }
	glEnd();
      }
  }
  else {
    
    Vector3D vertices_main[SIDE_NUMBER][VERTEX_PER_SIDE];
    Vector3D vertices_second[SIDE_NUMBER][VERTEX_PER_SIDE];    
    float RGB_main[3] = {1,0,0};
    float RGB_second[3] = {0.3,0.7,0};
    
    create_rectangle(game->get_main_rigidbody(), vertices_main, width, height, deepness); 
    create_rectangle(game->get_second_rigidbody(), vertices_second, width, height, deepness); 

    //first object
    for(int i = 0; i < SIDE_NUMBER; ++i)
      {
	glBegin(GL_POLYGON);
	glColor3f(RGB_main[0], RGB_main[1], RGB_main[2]);
	for(int j = 0 ; j < VERTEX_PER_SIDE; ++j)
	  {
	    glVertex3f(vertices_main[i][j].get_x(), vertices_main[i][j].get_y(), vertices_main[i][j].get_z());
	  }
	glEnd();
      }

    //second object
    for(int i = 0; i < SIDE_NUMBER; ++i)
      {
	glBegin(GL_POLYGON);
	glColor3f(RGB_second[0], RGB_second[1], RGB_second[2]);
	for(int j = 0 ; j < VERTEX_PER_SIDE; ++j)
	  {
	    glVertex3f(vertices_second[i][j].get_x(), vertices_second[i][j].get_y(), vertices_second[i][j].get_z());
	  }
	glEnd();
      }
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

// Catch the input of the player
void handler_event(unsigned char key, int x, int y) {
    switch(key) {
    case 'd':
      game->change_demo();
      exercice_1 = !exercice_1;
      break;
    }
  glutPostRedisplay();
}


// Print basic instructions for the player
void display_init(){
  printf("Phase 3 : Rotation on rigidbodies \n");
  printf("touch key d to change the demo !\n");
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
  glutKeyboardFunc(handler_event);
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_physic);
  gluLookAt(CAMERA_EYE_X, CAMERA_EYE_Y, CAMERA_EYE_Z, CAMERA_VIEW_X, CAMERA_VIEW_Y, CAMERA_VIEW_Z, CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);
  glutMainLoop();
  return 0;
}
