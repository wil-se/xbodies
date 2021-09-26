#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "glExtension.h"

#include <math.h>
#include <cstdlib>
#include <time.h>


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


int screenWidth = SCREEN_WIDTH;
int screenHeight = SCREEN_HEIGHT;


float angle=0.0f;
float lxcam=-60.0f,lzcam=-60.0f, lycam=-30.0f;
float xcam=10.0f,zcam=10.0f,ycam=10.0f;
float deltaAngle = 0.0f;
int xOrigin = -1;
int yOrigin = -1;
float camera_speed = 1.0f;

GLuint vboId = 0;

float *points;

int points_number = pow(2, 21);


void display();
void timer(int millisec);
void reshape(int w, int h);

void keyboard(unsigned char key, int /*x*/, int /*y*/);
void motion(int xcam, int ycam);
void timerEvent(int value);
void mouse(int button, int state, int xcam, int ycam);

void GLUTinit(int argc, char** argv);


int main(int argc, char** argv)
{  
    srand( (unsigned)time(NULL) );
    points = (float*)malloc(sizeof(float)*points_number*3);

    GLUTinit(argc, argv);

    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*points_number, 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*points_number, points); 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutMainLoop();

    return 0;
}

void GLUTinit(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(screenWidth, screenHeight);
    // glutInitWindowPosition(100, 100);
    glDisable(GL_DEPTH_TEST);
    glutCreateWindow("DOTS");
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)screenWidth / (GLfloat) screenHeight, 0.1, 1000000.0);
  
  

    glutDisplayFunc(display);
    glutTimerFunc(33, timer, 33);                 // redraw only every given millisec
    glutReshapeFunc(reshape);
    
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

}

void display()
{
    
    for(int i=0; i<points_number; i++){
        int index = i*3;
        for(int j=0; j<3; j++){
            int num = rand()%64;
            if(num%2==0){
                points[index+j] = num;
            } else {
                points[index+j] = -num;
            }

        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glPointSize(1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xcam,ycam, zcam, xcam+lxcam,ycam+lycam,zcam+lzcam, 0.0f,1.0f,0.0f);
    glutPostRedisplay();
    

     glBufferData(GL_ARRAY_BUFFER, sizeof(float)*points_number, 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*points_number, points);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    
    
    glDrawArrays(GL_POINTS, 0, points_number);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glPopMatrix();
    glutSwapBuffers();
}

void timer(int millisec)
{
    glLoadIdentity();
    gluLookAt(xcam,ycam, zcam, xcam+lxcam,ycam+lycam,zcam+lzcam, 0.0f,1.0f,0.0f);
    glutTimerFunc(millisec, timer, millisec);
    glutPostRedisplay();

}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat)w/(GLfloat)h, 1.0, 100000000000.0);
    glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
    switch (key)
    {
        case (27) :
            #if defined(__APPLE__) || defined(MACOSX)
                exit(EXIT_SUCCESS);
            #else
                glutDestroyWindow(glutGetWindow());
                return;
            #endif
        // W
        case (119) :
            // printf("W\n");
            xcam += lxcam * camera_speed;
            zcam += lzcam * camera_speed;
            return;
        // A
        case (97) :
            // printf("A\n");
            xcam += lxcam * camera_speed;
			ycam += lycam * camera_speed;
            return;
        // S
        case (115) :
            // printf("S\n");
            xcam -= lxcam * camera_speed;
            zcam -= lzcam * camera_speed;
            return;
        // D
        case (100) :
            // printf("D\n");
            xcam -= lxcam * camera_speed;
			ycam -= lycam * camera_speed;
            return;
    }
}

void motion(int xcam, int ycam)
{
    if (xOrigin >= 0) {
    deltaAngle = (xcam - xOrigin) * 0.005f;
    lxcam = sin(angle - deltaAngle) * camera_speed;
    lzcam = -cos(angle - deltaAngle) * camera_speed;
  }
  if (yOrigin >= 0) {
    deltaAngle = (ycam - yOrigin) * 0.005f;
    lycam = tan(angle - deltaAngle) * camera_speed;
  }
}


void mouse(int button, int state, int xcam, int ycam)
{
    
    if (button == GLUT_LEFT_BUTTON) {
    // printf("yooo\n");
    if (state == GLUT_UP) {
      angle -= deltaAngle;
      xOrigin = -1;
      yOrigin = -1;
    }
    else {
      xOrigin = xcam;
      yOrigin = ycam;
    }
  }
}