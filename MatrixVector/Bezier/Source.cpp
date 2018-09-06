// #include "Vector.h"
#include <iostream>
using namespace std;

#include "GL Libraries\GL\glut.h"
#include "Vector.h"

#define WINDOW_SIZE 800

void idle() {
	glutPostRedisplay();
}

void initCanvas() {
	// INIT CANVAS
	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

	// CLEAR
	glClearColor(0, 0, 0, 0);
}

void DrawLine(Vector v1, Vector v2) {
	glBegin(GL_LINES);

	glLineWidth(10);
	glColor3f(1, 1, 1);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);

	glEnd();
}

void DrawTriangle(Vector v1, Vector v2, Vector v3) {
	glBegin(GL_POLYGON);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);

	glEnd();
}

void DrawCircle(Vector point, int radius) {
	glPointSize(0.5); //ukuran titik/point

	// glRotatef(100, 1, 1, 1);
	for (float i = -3.14; i < 3.14; i += 0.0001)
	{
		float x = point.x + cos(i) * radius;
		float y = point.y + sin(i) * radius;

		glBegin(GL_POINTS);
		glVertex3f(x, y, 0);
		glEnd();
	}
}

void DrawKotak() {

}

void DisplayHouse() {
	///// CLEAR /////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glRotatef(1, 1, 1, 1);

	///// DRAW /////
	// SISI BAWAH
	DrawLine(Vector(-300, -300, 0, 1), Vector(300, -300, 0, 1));
	// ATAS
	DrawLine(Vector(-300, 300, 0, 1), Vector(300, 300, 0, 1));
	// KIRI
	DrawLine(Vector(-300, -300, 0, 1), Vector(-300, 300, 0, 1));
	// KANAN
	DrawLine(Vector(300, -300, 0, 1), Vector(300, 300, 0, 1));

	// ATAP
	DrawTriangle(Vector(-300, 300, 0, 1), Vector(300, 300, 0, 1), Vector(0, 600, 0, 1));
	// CEROBONG
	DrawLine(Vector(-250, 300, 0, 1), Vector(-250, 600, 0, 1));
	DrawLine(Vector(-100, 300, 0, 1), Vector(-100, 600, 0, 1));
	DrawLine(Vector(-100, 600, 0, 1), Vector(-250, 600, 0, 1));

	// PINTU
	// SISI KIRI
	DrawLine(Vector(-200, -300, 0, 1), Vector(-200, 50, 0, 1));
	// KANAN
	DrawLine(Vector(0, -300, 0, 1), Vector(0, 50, 0, 1));
	// ATAS
	DrawLine(Vector(-200, 50, 0, 1), Vector(0, 50, 0, 1));
	// BULAT
	DrawCircle(Vector(-175, -100, 0, 1), 10);

	// JENDELA
	// SISI KIRI & KANAN
	DrawLine(Vector(50, 200, 0, 1), Vector(50, 0, 0, 1));
	DrawLine(Vector(250, 200, 0, 1), Vector(250, 0, 0, 1));
	// SISI ATAS & BAWAH
	DrawLine(Vector(50, 0, 0, 1), Vector(250, 0, 0, 1));
	DrawLine(Vector(50, 200, 0, 1), Vector(250, 200, 0, 1));
	// KERANGKA JENDELA
	DrawLine(Vector(150, 0, 0, 1), Vector(150, 200, 0, 1));   // VERTICAL
	DrawLine(Vector(50, 100, 0, 1), Vector(250, 100, 0, 1)); //  HORIZONTAL

	///// DISPLAY /////
	glutSwapBuffers();
}

void main(int argc, char **argv) {
	// INIT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Bezier & Rumah");

	glutIdleFunc(idle);
	glutDisplayFunc(DisplayHouse);
	initCanvas();

	glutMainLoop();
}