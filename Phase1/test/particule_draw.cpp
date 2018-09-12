#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "../src/vector3D.hpp"
#include "../src/particule.hpp"

/* GLUT Particule Launcher animations

- 4 differents particules availables

*/

int WINDOW_SIZE = 1600;
int WINDOW_POSITION_X = 100;
int WINDOW_POSITION_Y = 100;

int CAMERA_EYE_X = 70;
int CAMERA_EYE_Y = -20;
int CAMERA_EYE_Z = 500;
int CAMERA_VIEW_X = 70;
int CAMERA_VIEW_Y = -20;
int CAMERA_VIEW_Z = 0;
int CAMERA_UP_X = 0;
int CAMERA_UP_Y = 1;
int CAMERA_UP_Z = 0;


Particule current;
Particule *container;

float animation_time = 10.0f;
float time;
float interval = 1.0/30.0;

Vector3D old_p;

bool launch = false;
bool stop = false;

// Display function called every frame
void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );


  Vector3D p = current.get_position();

  if(p.get_x() >= 200 && launch) {
    stop = true;

  }

//    glTranslated(p.get_x() - old_p.get_x(), p.get_y() - old_p.get_y(), p.get_z() - old_p.get_z());
    //glVertex3f(p.get_x(), p.get_y(), p.get_z());
    glutSolidSphere(1,30,30);

  old_p = p;
  glutSwapBuffers();
  glutPostRedisplay();
}

// Integration of the particule during the animation
void idle_func(void) {
  if(time < animation_time && !stop && launch) {
    //give to integrate the time between two frame
    current.integrate(interval);
    time += interval;
    //multiply by 1000 due to sleep function taking millisecond in argument.
    usleep(interval*1000);
  }
  else if( (time >= animation_time || stop) && launch) {
    stop = false;
    launch = false;
    time = 0.0f;
    old_p = Vector3D();
    glPopMatrix();
    printf("End of animation !\n");
  }
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
		 500
		 );
  glMatrixMode(GL_MODELVIEW);
}

// Initialisation of the 4 types of particules
void init_particules() {
  int size = 4;
  Particule gun_bullet = Particule(Vector3D(), Vector3D(35,0,0), 2, 1, 0.7);
  Particule fire_ball = Particule(Vector3D(), Vector3D(50,0,0), 2, -1, 0.7);
  Particule laser = Particule(Vector3D(), Vector3D(100,0,0), 2, 0, 0.7);
  Particule canon = Particule(Vector3D(), Vector3D(70,0,0), 2, 6, 0.7);

  container = new Particule[size]();
  container[0] = gun_bullet;
  container[1] = fire_ball;
  container[2] = laser;
  container[3] = canon;

  current = *(container);
}

// Catch the input of the player
void handler_event(unsigned char key, int x, int y) {
  int end = 577 - (577/2) - CAMERA_EYE_X;
  if(launch == false) {
    switch(key) {
    case '1':
      current = container[0];
      glColor3f(1.0,1.0,1.0);
      glTranslated(end, 0, 0);
      break;
    case '2':
      current = container[1];
      glColor3f(1.0,0.0,0.0);
      break;
    case '3':
      current = container[2];
      glColor3f(0.0,1.0,0.0);
      break;
    case '4':
      current = container[3];
      glColor3f(0.0,0.0,1.0);
      break;
    case 'l':
      printf("Particule launched ! \n");
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
  printf("Welcome to the Particule Launcher !\n");
  printf("You have 4 particules availables : gun bullet, fire ball, laser and canon. Push 1 to 4 respectively to choose one.\n");
  printf("Then push `l` to launch the particule.\n");
  printf("When the animation is over, you can start again by choosing a particule and launching it.\n");
}

int main(int argc, char** argv)
{
  time = 0.0f;
  old_p = Vector3D();

  init_particules();

  display_init();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
  glutCreateWindow("particule launcher");
  glutKeyboardFunc(handler_event);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle_func);
  gluLookAt(CAMERA_EYE_X, CAMERA_EYE_Y, CAMERA_EYE_Z, CAMERA_VIEW_X, CAMERA_VIEW_Y, CAMERA_VIEW_Z, CAMERA_UP_X, CAMERA_UP_Y, CAMERA_UP_Z);

  glutMainLoop();
  return 0;
}
