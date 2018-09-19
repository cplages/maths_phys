#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <vector>


#include "../src/vector3D.hpp"
#include "../src/particule.hpp"


using namespace std;

/* GLUT Particule Launcher animations

- 4 differents particules availables

*/

int WINDOW_SIZE = 1600;
int WINDOW_POSITION_X = 100;
int WINDOW_POSITION_Y = 100;

int CAMERA_EYE_X = 150;
int CAMERA_EYE_Y = -20;
int CAMERA_EYE_Z = 250;
int CAMERA_VIEW_X = 150;
int CAMERA_VIEW_Y = -20;
int CAMERA_VIEW_Z = 0;
int CAMERA_UP_X = 0;
int CAMERA_UP_Y = 1;
int CAMERA_UP_Z = 0;

vector<Particule> particule_types;
vector<Particule> particule_instances;

float animation_time = 10.0f;
float current_time;
float interval = 1.0/30.0;

Vector3D old_p;

bool launch = false;

// Display function called every frame
void display(void)
{
  glClear
    (
     GL_COLOR_BUFFER_BIT |
     GL_DEPTH_BUFFER_BIT
     );

  for(vector<Particule>::iterator it = particule_instances.begin(); it != particule_instances.end(); ++it)
    {
      Vector3D p = it->get_position();

      glTranslated(p.get_x() - old_p.get_x(), p.get_y() - old_p.get_y(), p.get_z() - old_p.get_z());
      glutSolidSphere(1,30,30);
  
      old_p = p;
    }
  glutSwapBuffers();
  glutPostRedisplay();
}

// Integration of the particule during the animation
void idle_func(void) {
  clock_t start_time = clock();
  if(current_time < animation_time && launch) {
    //give to integrate the time between two frame
    for(vector<Particule>::iterator it = particule_instances.begin(); it != particule_instances.end(); ++it)
      {
	it->integrate(interval);
      }
    
    current_time += interval;    
    float remaining_time = interval - (clock() - start_time) / CLOCKS_PER_SEC;
    if(remaining_time > 0) {
      //multiply by 1000 due to sleep function taking millisecond in argument.
      usleep(remaining_time * 1000);
    }
  }
  else if( current_time >= animation_time  && launch) {
    launch = false;
    current_time = 0.0f;
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
		 250
		 );
  glMatrixMode(GL_MODELVIEW);
}

// Initialisation of the 4 types of particules
void init_particules_types() {
  int size = 4;
  Particule gun_bullet = Particule(Vector3D(), Vector3D(35,0,0), 2, 1, 0.7);
  Particule fire_ball = Particule(Vector3D(), Vector3D(50,0,0), 2, -1, 0.7);
  Particule laser = Particule(Vector3D(), Vector3D(100,0,0), 2, 0, 0.7);
  Particule canon = Particule(Vector3D(), Vector3D(70,0,0), 2, 6, 0.7);

  particule_types.push_back(gun_bullet);
  particule_types.push_back(fire_ball);
  particule_types.push_back(laser);
  particule_types.push_back(canon);

  particule_instances.push_back(particule_types[0]);

}

// Catch the input of the player
void handler_event(unsigned char key, int x, int y) {
  if(launch == false) {
    switch(key) {
    case '1':
      particule_instances[0] = particule_types[0];
      glColor3f(1.0,1.0,1.0);
      break;
    case '2':
      particule_instances[0] = particule_types[1];
      glColor3f(1.0,0.0,0.0);
      break;
    case '3':
      particule_instances[0] = particule_types[2];
      glColor3f(0.0,1.0,0.0);
      break;
    case '4':
      particule_instances[0] = particule_types[3];
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
  current_time = 0.0f;
  old_p = Vector3D();

  init_particules_types();

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
