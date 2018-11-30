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

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, WINDOW_SIZE * 2, WINDOW_SIZE * 2);
	glLoadIdentity();
	gluPerspective(90, 1, 0.02, 50);
	glEnable(GL_DEPTH_TEST);
}

void test() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPointSize(2);

	mesh.drawMesh(cam);
	// mesh.drawMesh_(cam);

	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) {
	if (key == 'p') {
		cam.change_view_y(-10);
	}
	else if (key == 'a') {
		cam.change_view_x(10);
	}
	else if (key == 'l') {
		cam.change_view_y(10);
	}
	else if (key == 'd') {
		cam.change_view_x(-10);
	}
	else if (key == 'w') {
		cam.change_view_z(-10);
	}
	else if (key == 's') {
		cam.change_view_z(10);
	}
	else if (key == 'h') {
		cam.rotate(Vector(1, 0, 0, 1), 3);
	}
	else if (key == 'j') {
		cam.rotate(Vector(-1, 0, 0, 1), 3);
	}
	else if (key == 'q') {
		cam.rotate(Vector(0, 1, 0, 1), 3);
	}
	else if (key == 'e') {
		cam.rotate(Vector(0, -1, 0, 1), 3);
	}
	else if (key == 'k') {
		cam.rotate(Vector(0, 0, 1, 1), 3);
	}
	else if (key == 'i') {
		cam.rotate(Vector(0, 0, 1, 1), -3);
	}
}

void main(int argc, char **argv) {

	// mesh.loadObject("teko.txt");
	mesh.loadObject("house.obj");
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