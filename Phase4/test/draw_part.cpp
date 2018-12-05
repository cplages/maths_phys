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
#include "../src/plane.hpp"

#include "game_world.hpp"

using namespace std;

//current exercice
bool exercice_1 = true;

// physic handler
GameWorld *game;


float current_time;



// apply physic to the game
void update_physic(){
  //  game->execute(&current_time);
  glutPostRedisplay();
}

//create all vertices for a cube.
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

  //put the coordinate in the world.
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
  float width = 10;
  float height = 5;
  float deepness = 2;
  //Vector3D vertices[SIDE_NUMBER][VERTEX_PER_SIDE];    
  float RGB[3] = {1,0,0};
    
  //create_rectangle(game->get_main_rigidbody(), vertices, width, height, deepness); 

  Rigidbody r = Rigidbody();
  Plane plane = Plane(&r, 10,5,2);

  Vector3D * vertices = plane.get_vertex();

  float coeff = 0;
  float coeff_x = 4;
  float coeff_y = 2;
  float coeff_z = 1;
  glBegin(GL_POLYGON);
  glColor3f(RGB[0], RGB[1], RGB[2]);
  //x_lock
  coeff = 4;
  printf("vertex coordinate\n");
  for(int i = 0; i < 2; ++i) {
    for(int j = 0; j < 4; ++j) {
      int index = i * coeff + j;
      printf("%d,", index);
      glVertex3f(vertices[index].get_x(), vertices[index].get_y(), vertices[index].get_z());
    }
    printf("\n");
  }

  
  //y_lock
  coeff = 2;
  for(int i = 0; i < 2; ++i) {
    for(int j = 0; j < 2; ++j) {
      	int index = i * coeff + j ;
	printf("%d,", index);
	glVertex3f(vertices[index].get_x(), vertices[index].get_y(), vertices[index].get_z());
    }
    for(int k = 2; k > 0; --k) {
      int index = i * coeff + coeff_x + (k-1) ;
	printf("%d,", index);
	glVertex3f(vertices[index].get_x(), vertices[index].get_y(), vertices[index].get_z());
    }
    printf("\n");
  }
  

  //z_lock
  coeff = 1;
  for(int i = 0; i < 2; ++i) {
    for(int j = 0; j < 2; ++j) {
      int index = i * coeff + j * coeff_y;
      printf("%d,", index);
      glVertex3f(vertices[index].get_x(), vertices[index].get_y(), vertices[index].get_z());
    }
    for(int k = 2; k > 0; --k) {
      int index = i * coeff + (k + 1) * coeff_y ;
      printf("%d,", index);
      glVertex3f(vertices[index].get_x(), vertices[index].get_y(), vertices[index].get_z());
    }
    printf("\n");
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

// Catch the input of the player
void handler_event(unsigned char key, int x, int y) {
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
