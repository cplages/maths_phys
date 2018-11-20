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

// physic handler
GameWorld *game;

int side_number = 6;
int vertex_per_side = 4;

//rigidbody color
float RGB[6][3];

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

  Vector3D p = game->get_rigidbody()->get_position();
  float width = 0.5;
  float height = 1;
  float deepness = 1;

  Vector3D vertices[side_number][vertex_per_side];
  //back side
  //red
  RGB[0][0] = 1;
  RGB[0][1] = 0;
  RGB[0][2] = 0;
  //side
  vertices[0][0] = Vector3D(-width, -height, -deepness);
  vertices[0][1] = Vector3D(width, -height, -deepness);
  vertices[0][2] = Vector3D(width, height, -deepness);
  vertices[0][3] = Vector3D(-width, height, -deepness);

  //bottom side
  RGB[1][0] = 0.5;
  RGB[1][1] = 1;
  RGB[1][2] = 0;
  vertices[1][0] = Vector3D(-width, -height, -deepness);
  vertices[1][1] = Vector3D(width, -height, -deepness);
  vertices[1][2] = Vector3D(width, -height, deepness);
  vertices[1][3] = Vector3D(-width, -height, deepness);
  
  //left side
  //orange
  RGB[2][0] = 1;
  RGB[2][1] = 0.5;
  RGB[2][2] = 0;
  vertices[2][0] = Vector3D(-width, -height, -deepness);
  vertices[2][1] = Vector3D(-width, height, -deepness);
  vertices[2][2] = Vector3D(-width, height, deepness);
  vertices[2][3] = Vector3D(-width, -height, deepness);

    //right side
  RGB[3][0] = 1;
  RGB[3][1] = 1;
  RGB[3][2] = 0;
  vertices[3][0] = Vector3D(width, -height, -deepness);
  vertices[3][1] = Vector3D(width, height, -deepness);
  vertices[3][2] = Vector3D(width, height, deepness);
  vertices[3][3] = Vector3D(width, -height, deepness);

  
  //up side
  RGB[4][0] = 1;
  RGB[4][1] = 1;
  RGB[4][2] = 1;
  vertices[4][0] = Vector3D(-width, height, -deepness);
  vertices[4][1] = Vector3D(width, height, -deepness);
  vertices[4][2] = Vector3D(width, height, deepness);
  vertices[4][3] = Vector3D(-width, height, deepness);

  //front side
  RGB[5][0] = 0;
  RGB[5][1] = 0;
  RGB[5][2] = 1;
  vertices[5][0] = Vector3D(-width, -height, deepness);
  vertices[5][1] = Vector3D(width, -height, deepness);
  vertices[5][2] = Vector3D(width, height, deepness);
  vertices[5][3] = Vector3D(-width, height, deepness);

  int size = side_number * vertex_per_side * 3;
  GLfloat vertex_buffer_data[size] = {0};
  for(int i =5 ; i < side_number; ++i)
  {
    for(int j = 0 ; j < vertex_per_side; ++j) {
      vertices[i][j] = game->get_rigidbody()->local_to_world(vertices[i][j]);
      // vertex_buffer_data[vertex_per_side * i + j * 3] = tmp.get_x();
      // vertex_buffer_data[vertex_per_side * i + j * 3 + 1] = tmp.get_y();
      // vertex_buffer_data[vertex_per_side * i + j * 3 + 2] = tmp.get_z();
    }
  }
  for(int i = 0; i < vertex_per_side - 1; ++i) {
    printf("distance d'un côté: %f\n", vertices[5][i].distance(&vertices[5][i+1]));
  }
  printf("distance d'un côté: %f\n", vertices[5][0].distance(&vertices[5][vertex_per_side - 1]));
  
  printf("\n");
  /*GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, size, vertex_buffer_data, GL_STATIC_DRAW);*/
  
  for(int i = 5; i < side_number; ++i)
  {
    glBegin(GL_POLYGON);
    glColor3f(RGB[i][0], RGB[i][1], RGB[i][2]);
    for(int j = 0 ; j < vertex_per_side; ++j)
      {
	glVertex3f(vertices[i][j].get_x(), vertices[i][j].get_y(), vertices[i][j].get_z());
      }
    glEnd();
    }
  
  /*  GLfloat color_buffer_data[side_number * vertex_per_side *3] = {0};
  for(int i =0 ; i < side_number; ++i)
  {
    for(int j = 0 ; j < vertex_per_side; ++j) {
      vertex_buffer_data[vertex_per_side * i + j * 3] = RGB[i][0];
      vertex_buffer_data[vertex_per_side * i + j * 3 + 1] = RGB[i][1];
      vertex_buffer_data[vertex_per_side * i + j * 3 + 2] = RGB[i][2];
    }
  }

  
  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);

  
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

  // 2nd attribute buffer : colors
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

  // Draw the triangle !
  glDrawArrays(GL_QUADS, 0, size); // 12*3 indices starting at 0 -> 12 triangles

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);*/

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
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_physic);
  gluLookAt(CAMERA_EYE_X, CAMERA_EYE_Y, CAMERA_EYE_Z, CAMERA_VIEW_X, CAMERA_VIEW_Y, CAMERA_VIEW_Z, CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);
  printf("gravity value! : %f\n", GRAVITY_VALUE);
  glutMainLoop();
  return 0;
}
