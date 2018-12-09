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


// physic handler
GameWorld *game;

float current_time;

bool display_occured = false;

// apply physic to the game
void update_physic(){
  if(!game->collision_occured()) {
    game->execute(&current_time);
  }
  else{
    if(!display_occured) {
      game->display_contact();
      display_occured = true;
    }
  }
  glutPostRedisplay();
}

// Create box vertices sorted by faces
Vector3D * vertices_to_object_faces(Box * box){

    Vector3D * vertices = box->get_vertices();

    Vector3D * faces_coord = new Vector3D[24];
    int current_index = 0;

    float coeff = 0;
    float coeff_x = 4;
    float coeff_y = 2;
    float coeff_z = 1;

    //x_lock
    coeff = 4;
    for(int i = 0; i < 2; ++i) {
      for(int j = 0; j < 4; ++j) {
        int index = i * coeff + j;
        faces_coord[current_index] = vertices[index];
        current_index++;
      }
    }

    //y_lock
    coeff = 2;
    for(int i = 0; i < 2; ++i) {
      for(int j = 0; j < 2; ++j) {
        int index = i * coeff + j ;
        faces_coord[current_index] = vertices[index];
        current_index++;
      }
      for(int k = 2; k > 0; --k) {
        int index = i * coeff + coeff_x + (k-1) ;
        faces_coord[current_index] = vertices[index];
        current_index++;
      }
    }

    //z_lock
    coeff = 1;
    for(int i = 0; i < 2; ++i) {
      for(int j = 0; j < 2; ++j) {
        int index = i * coeff + j * coeff_y;
        faces_coord[current_index] = vertices[index];
        current_index++;
      }
      for(int k = 2; k > 0; --k) {
        int index = i * coeff + (k + 1) * coeff_y ;
        faces_coord[current_index] = vertices[index];
        current_index++;
      }
    }

    return faces_coord;
}

// Simulate wall from a plan
Vector3D * plane_to_vertices(Plane plane){

  float offset = plane.get_offset();
  Vector3D normal = plane.get_normal();

  Vector3D * plane_vertices = new Vector3D[4];

  if (normal.get_x() != 0){
    plane_vertices[0] = normal * (-offset) + Vector3D(0,-HALF_HEIGHT, -HALF_WIDTH);
    plane_vertices[1] = normal * (-offset) + Vector3D(0,-HALF_HEIGHT, HALF_WIDTH);
    plane_vertices[2] = normal * (-offset) + Vector3D(0, HALF_HEIGHT, HALF_WIDTH);
    plane_vertices[3] = normal * (-offset) + Vector3D(0, HALF_HEIGHT, -HALF_WIDTH);
  }
  else if (normal.get_y() != 0){
    plane_vertices[0] = normal * (-offset) + Vector3D(-HALF_WIDTH, 0, -HALF_HEIGHT);
    plane_vertices[1] = normal * (-offset) + Vector3D(HALF_WIDTH, 0, -HALF_HEIGHT);
    plane_vertices[2] = normal * (-offset) + Vector3D(HALF_WIDTH, 0, HALF_HEIGHT);
    plane_vertices[3] = normal * (-offset) + Vector3D(-HALF_WIDTH, 0, HALF_HEIGHT);
  }
  else if (normal.get_z() != 0){
    plane_vertices[0] = normal * (-offset) + Vector3D(-HALF_WIDTH, -HALF_HEIGHT, 0);
    plane_vertices[1] = normal * (-offset) + Vector3D(HALF_WIDTH, -HALF_HEIGHT, 0);
    plane_vertices[2] = normal * (-offset) + Vector3D(HALF_WIDTH, HALF_HEIGHT, 0);
    plane_vertices[3] = normal * (-offset) + Vector3D(-HALF_WIDTH, HALF_HEIGHT, 0);
  }

  return plane_vertices;
}

// Display function called every frame
void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );

  float RGB_box[3] = {1,0,0};
  float RGB_collision_wall[3] = {0.8  , 0.5, 0};
  float RGB_plane[5][3] = { {0,0,0.5}, {0,0.5,0}, {0,0.5,0.5}, {0,1,1}, {0,0,1}};

  Vector3D * box_vertices_to_draw = vertices_to_object_faces(game->get_main_box());
  Plane * walls = game->get_walls();

  Plane * collision_wall = NULL;

  //Planes
  for (int i = 0; i < 5;  i++){
    Vector3D * plane_vertices_to_draw = plane_to_vertices(walls[i]);
    if(display_occured) {
      if(walls[i].get_normal() == game->get_normal_contact()) {
        collision_wall = &walls[i];
      }
    }
    glBegin(GL_POLYGON);
    glColor3f(RGB_plane[i][0], RGB_plane[i][1], RGB_plane[i][2]);
    for (int j = 0; j < 4; j++){
      glVertex3f(plane_vertices_to_draw[j].get_x(), plane_vertices_to_draw[j].get_y(), plane_vertices_to_draw[j].get_z());
    }
    glEnd();
  }

  //Re draw the collision wall in a different color
  glBegin(GL_POLYGON);
  glColor3f(RGB_collision_wall[0], RGB_collision_wall[1], RGB_collision_wall[2]);
  if(display_occured)
  {
    Vector3D * plane_vertices_to_draw = plane_to_vertices(*collision_wall);
    for (int j = 0; j < 4; j++){
      glVertex3f(plane_vertices_to_draw[j].get_x(), plane_vertices_to_draw[j].get_y(), plane_vertices_to_draw[j].get_z());
    }
  }
  glEnd();

  //Box
  glBegin(GL_POLYGON);
  glColor3f(RGB_box[0], RGB_box[1], RGB_box[2]);
  for (int i = 0; i <  24; i++){
    glVertex3f(box_vertices_to_draw[i].get_x(), box_vertices_to_draw[i].get_y(), box_vertices_to_draw[i].get_z());
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
  if(key == 'x') {
    game = new GameWorld(Vector3D(1,0,0));
    display_occured = false;
  }
  else if( key == 'y') {
    game = new GameWorld(Vector3D(0,1,0));
    display_occured = false;
  }
  else if (key == 'z') {
    game = new GameWorld(Vector3D(0,0,-1));
    display_occured = false;
  }
  else if (key == 'c') {
    game = new GameWorld(Vector3D(1,1,0));
    display_occured = false;
  }
  glutPostRedisplay();
}


// Print basic instructions for the player
void display_init(){
  printf("Phase 4: Collision detection between planes and a box \n");
}

//init opengl functions and game parameters.
int main(int argc, char** argv)
{
  current_time = 0;


  //initiate game physics.
  game = new GameWorld(Vector3D(0,0,0));

  display_init();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow("Collision detectection of a box in a room");
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
