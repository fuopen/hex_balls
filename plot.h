#ifndef _PLOT_H_
#define _PLOT_H_
#include<GL/glut.h>
#include "singvex.h"

GLuint list_id;
int winWidth,winHeight;
float angle= 0.0,axis[3],trans[3];
bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;

float lastPos[3]={0.0,0.0,0.0};

int curx,cury;
int startX,startY;

void my_init();
void my_reshape(int w,int h);
void my_display();
void my_draw();
void my_list();
void trackball_ptov(int,int,int,int,float[]);
void mouseMotion(int,int);
void startMotion(int,int);
void stopMotion(int,int);
void mouseButton(int,int,int,int);
void spin_obj();

#endif
