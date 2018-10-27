#include <fstream>

#include <iostream>
using namespace std;

#include "GL Libraries\GL\glut.h"
#include "Header.h"

#define WINDOW_SIZE 600

Mesh mesh;
Transformation transform;
Camera cam;

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

	// glRotatef(1, 1, 1, 1);

	glPointSize(2);

	mesh.drawMesh(cam);
	
	glDisable(GL_TEXTURE_2D);

	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 'w') {
		cam.change_view_y(-6);
	}
	else if (key == 'a') {
		cam.change_view_x(6);
	}
	else if (key == 's') {
		cam.change_view_y(6);
	}
	else if (key == 'd') {
		cam.change_view_x(-6);
	}
	else if (key == 'p') {
		cam.change_view_z(-6);
	}
	else if (key == 'l') {
		cam.change_view_z(6);
	}
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

	glutKeyboardFunc(keyPressed);

	glutMainLoop();
	
}