#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

double x_camera = 0.0;
double y_camera = 0.0;
double z_camera = 0.0;
double speed = 1.0;
double a = 0;

void displayMe(void)
{
  GLint color[] = {0, 0, 0, 1};
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
  glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
  glClear
      (
       GL_COLOR_BUFFER_BIT |
       GL_DEPTH_BUFFER_BIT
       );
  glMatrixMode(GL_MODELVIEW);
  glTranslated(0,0,-5);

    glutSolidSphere(1,30,30);
    glLoadIdentity();
    gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
    //triangle blanc
    /*glBegin(GL_TRIANGLES);

    glVertex2i(0,1);
    glVertex2i(-1,0);
    glVertex2i(1,0);

    glEnd();*/

    //glRotated(a*180/3.14,1,1,1);
    //glTranslated(cos(a), 0, sin(a));
    /*glScaled(1. -cos(a)/3.,1.+cos(a)/3.,1.+cos(a)/3.);*/
    //a += 0.1;
    /*glBegin(GL_LINES);
    glVertex2i(0,0);glVertex2i(0,1);
    glVertex2i(0,0);glVertex2i(1,0);
    glVertex2i(0,0);glVertex3i(0,0,1);
    glEnd();*/
    
    
    glutSwapBuffers();

    glutPostRedisplay();
}

// void handler_event(unsigned char key, int x, int y) {
//   switch(key) {
//   case 'z':
//     z_camera += speed;
//     break;
//   case 's':
//     z_camera -= speed;
//     break;
//   case 'q':
//     x_camera -= speed;
//     break;
//   case 'd':
//     x_camera += speed;
//     break;
//   }
//   gluLookAt(x_camera, y_camera, z_camera,0.0,0.0,0.0,0.0,1.0,0.0);
//   printf("x: %f, y: %f, z: %f \n", x_camera, y_camera, z_camera);
//   displayMe();
// }



int WindowName;

void Reshape(int width, int height)
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
  printf("reshape called! \n");
}

void InitGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  //glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    WindowName = glutCreateWindow("Hello world :D");
    
    //glutKeyboardFunc(handler_event);
    glutDisplayFunc(displayMe);
    glutReshapeFunc(Reshape);
    InitGL();
    
    glutMainLoop();
    return 0;
}
