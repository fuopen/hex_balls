#include "plot.h"
extern singvex sigvx;
void my_init(){

	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glMatrixMode(GL_MODELVIEW);

	GLfloat mat_ambient[4]     = {0.20,0.20,0.20,1.0};
	GLfloat diffuseMaterial[4] = {0.80,0.80,0.80,1.0};//{1.0,1.0,1.0,1.0};
	GLfloat mat_specular[4]    = {0.00,0.00,0.01,1.0};//{0.34,0.45,0.45,1.0};

	GLfloat light0_position[4]  = {1.0,1.0,1.0,0.0};
	GLfloat light0_ambient[4]   = {1.0,1.0,1.0,1.0};//{0.7,0.4,0.88,1.0};
	GLfloat light0_diffuse[4]   = {1.0,0.93,0.93,1.0};//{0.3,0.2,0.3,1.0};
	GLfloat light0_specular[4]  = {0.0,1.0,0.0,1.0};//{0.22,0.42,0.01,1.0};

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseMaterial);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,200.0);

	glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light0_specular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	//sigvx.print();
}

void my_draw(){
	for(unsigned i=0;i<18;i++){
		if(i/6==0||i/6==2){
			glBegin(GL_TRIANGLES);
				for(int j=0;j<3;j++){
					glColor3f(0.23,0.88*(i+1.0)/18.0,0.32);
					int i0 = sigvx.get_pg(i,j);
					glVertex3f(sigvx.get_sp(i0,0),sigvx.get_sp(i0,1),sigvx.get_sp(i0,2));
				}
			glEnd();
		}
		else{
			glBegin(GL_QUADS);
				for(int j=0;j<4;j++){
					glColor3f(0.52,0.34*(i+1)/21.1,0.65*(i+1)/19.34);
					int i0 = sigvx.get_pg(i,j);
					glVertex3f(sigvx.get_sp(i0,0),sigvx.get_sp(i0,1),sigvx.get_sp(i0,2));
				}
			glEnd();
		}
	}
}
					

void my_list(){
	list_id = glGenLists(1);
	glNewList(list_id,GL_COMPILE_AND_EXECUTE);
		my_draw();
	glEndList();
}

void my_display(){
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(trackballMove) glRotatef(angle,axis[0],axis[1],axis[2]);
	my_list();
	glCallList(list_id);
	glutSwapBuffers();
	glFlush();
}


void trackball_ptov(int x, int y, int width, int height, float v[3]){
    float d, a;
    /* project x,y onto a hemisphere centered within width, height */
    v[0] = (2.0F*x - width) / width;
    v[1] = (height - 2.0F*y) / height;
    d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);
    v[2] = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));
    a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}


void mouseMotion(int x, int y){
    float curPos[3], dx, dy, dz;
    trackball_ptov(x, y, winWidth, winHeight, curPos);
	if(trackingMouse){
    	dx = curPos[0] - lastPos[0];
    	dy = curPos[1] - lastPos[1];
    	dz = curPos[2] - lastPos[2];

    	if(dx || dy || dz){
			angle = 90.0F * sqrt(dx*dx + dy*dy + dz*dz);
			axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
			axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
			axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

			lastPos[0] = curPos[0];
			lastPos[1] = curPos[1];
			lastPos[2] = curPos[2];
		}
	} 
	glutPostRedisplay();
}

void startMotion(int x, int y){

    trackingMouse = true;
    redrawContinue = false;
    startX = x; startY = y;
    curx = x; cury = y;
    trackball_ptov(x, y, winWidth, winHeight, lastPos);
	trackballMove=true;
}

void stopMotion(int x, int y){

    trackingMouse = false;
    if(startX != x || startY != y){
		redrawContinue = true;
    } 
	else{
		angle = 0.0F;
		redrawContinue = false;
		trackballMove = false;
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if(button==GLUT_RIGHT_BUTTON) exit(0);
	if(button==GLUT_LEFT_BUTTON)	switch(state) 
	{
				case GLUT_DOWN:
				y=winHeight-y;
				startMotion(x,y);
				break;
				case GLUT_UP:
				stopMotion(x,y);
				break;
							} 
}

void myReshape(int w, int h)
{
      glViewport(0, 0, w, h);
      winWidth = w;
      winHeight = h;
}
 
void spin_obj()
{
       if (redrawContinue)	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("colorcube");
	my_init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(my_display);
    glutIdleFunc(spin_obj);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
	glEnable(GL_DEPTH_TEST); 
    glutMainLoop();
}
