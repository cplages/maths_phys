#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "../src/vector3D.hpp"
#include "../src/particule.hpp"

int WINDOW_SIZE = 1600;

Particule current;
Particule *container;

float animation_time = 10.0f;
float time;
float interval = 1.0/30.0;

Vector3D old_p;

bool launch = false;

void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );
  
  
  Vector3D p = current.get_position();
  
  glTranslated(p.get_x() - old_p.get_x(), p.get_y() - old_p.get_y(), p.get_z() - old_p.get_z());
  glutSolidSphere(1,30,30);
  old_p = p;

  glutSwapBuffers();
  glutPostRedisplay();
}

void idle_func(void) {
  if(time < animation_time && launch) {
    //give to integer the time between two frame
    current.integer(interval);
    time += interval;
    current.display();
    printf("time: %f \n", time);
    //multiply by 1000 due to sleep function taking millisecond in argument.
    usleep(interval*1000);
  }
  else if( time >= animation_time && launch) {
    launch = false;
    time = 0.0f;
    old_p = Vector3D();
    glPopMatrix();
  }
  glutPostRedisplay();
}

void reshape(int width, int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
		 45,
		 float(width)/float(height),
		 0.1,
		 100
		 );
  glMatrixMode(GL_MODELVIEW);
}

void init_particules() {
  int size = 4;
  Particule gun_bullet = Particule(Vector3D(), Vector3D(35,0,0), 2, 1, 0.70);
  Particule fire_ball = Particule(Vector3D(), Vector3D(50,0,0), 2, -1, 0.70);
  Particule paper_ball = Particule(Vector3D(), Vector3D(5,0,0), 2, 0.1, 0.70);
  Particule canon = Particule(Vector3D(), Vector3D(70,0,0), 2, 6, 0.70);

  container = new Particule[size]();
  container[0] = gun_bullet;
  container[1] = fire_ball;
  container[2] = paper_ball;
  container[3] = canon;

  current = *(container);
}

void handler_event(unsigned char key, int x, int y) {
  if(launch == false) {
    switch(key) {
    case '1':
      current = container[0];
      glColor3f(1.0,1.0,1.0);
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
      launch = true;
      glPushMatrix();
      break;
    default:
      break;
    }
  }
  glutPostRedisplay();
}


int main(int argc, char** argv)
{
  time = 0.0f;
  old_p = Vector3D();

  init_particules();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("particule launcher");
  gluLookAt(70, -20, 100, 70, -20, 0, 0, 1, 0);  
  glutKeyboardFunc(handler_event);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle_func);
  //    InitGL();
  
  glutMainLoop();
  return 0;
}
