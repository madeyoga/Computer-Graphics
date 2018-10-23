#include <fstream>

#include <iostream>
using namespace std;

#include "GL Libraries\GL\glut.h"
#include "Header.h"

#define WINDOW_SIZE 600

Mesh mesh;
Transformation transform;

void idle() {
	glutPostRedisplay();
}

void initWorld() {
	// INIT CANVAS
	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

	// CLEAR
	glClearColor(0, 0, 0, 0);
}

void test() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(1, 1, 1, 1);

	glPointSize(2);

	mesh.drawMesh();
	
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

void main(int argc, char **argv) {

	mesh.loadObject("teko.txt");
	// INIT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("test 2!");

	glutIdleFunc(idle);
	glutDisplayFunc(test);
	initWorld();

	// glutMouseFunc(OnMouseClick);

	glutMainLoop();

}