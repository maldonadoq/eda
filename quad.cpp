#include <iostream>
#include <GL/glut.h>

#define KEY_ESC 27

double glsize = 600;
const double xmn = -90, xmx = 90, ymn = -180, ymx = 180;

#include "src/setvalue.h"
#include "src/quadtree.h"

#define T double
#define D string

using namespace std;

typedef quadtree<T,D>	qtree;
typedef qnode<D>		node;

qtree *test;

void gldraw(){
	glBegin(GL_LINES);
		for(unsigned i=0; i<vlines.size(); i+=2){
			glColor3d(0,255,0);
			glVertex2d(vlines[i].x,vlines[i].y);
			glVertex2d(vlines[i+1].x,vlines[i+1].y);
		}		
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
		glColor3d(255,0,0);
    	for(unsigned i=0; i<vpoints.size(); i++)
    		glVertex2d(vpoints[i].x,vpoints[i].y);
	glEnd();
}

void glpaint(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(xmin,xmax,ymin,ymax, -1.0f, 1.0f);
	gldraw();
	glutSwapBuffers();
}

void idle(){	glutPostRedisplay();	}

void init_GL(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(xmin,xmax,ymin,ymax,-1.0f,1.0f);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
		case KEY_ESC:
			exit(0);
			break;
		default:
			break;
	}
}

int main(int argc, char *argv[]){	
	test = new qtree(qpoint(xmn,ymn), qpoint(xmx,ymx),QDMIN);
	test->rdfile("data/crime.csv");
	test->qtsaveline();
	cout << "xmin: " << xmin << endl;
    cout << "xmax: " << xmax << endl;
    cout << "ymin: " << ymin << endl;
    cout << "ymax: " << ymax << endl;
	cout << "[CREATED]" << endl;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(glsize, glsize);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("QuadTree");
	init_GL();

	glutDisplayFunc(glpaint);

	glutReshapeFunc(&window_redraw);
	glutKeyboardFunc(&window_key);
	glutIdleFunc(&idle);

	glutMainLoop();
	return 0;
}
