// #include "Vector.h"
#include <iostream>
#include <vector>
using namespace std;

#include "GL Libraries\GL\glut.h"
#include "Vector.h"

#define WINDOW_SIZE 800

vector <Vector> points;

float factorial(int n) {
	if (n <= 1)
		return(1);
	else
		n = n*factorial(n - 1);
	return n;
}

float kombinasi(float n, float k) {
	float result = factorial(n) / (factorial(k)*factorial(n - k));
	return result;
}

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

void DrawHalfCircle(Vector point, int radius) {
	glPointSize(0.5); //ukuran titik/point

	for (float i = -1.57; i < 1.57; i += 0.0001)
	{
		float x = point.x + cos(i) * radius;
		float y = point.y + sin(i) * radius;

		glBegin(GL_POINTS);
		glVertex3f(x, y, 0);
		glEnd();
	}
}

void DrawCircle(Vector point, int radius) {
	glPointSize(0.5); //ukuran titik/point

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

Vector get_calculated_bezier_point(vector<Vector> v, float t) {
	int size = v.size();
	float x = 0, y = 0;
	for (int i = 0; i < size; i++) {
		// x += kombinasi((float)(size - 1), (float)i) * pow((1 - t) * 1.0, (size - i - 1) * 1.0) * pow(t*1.0, i) * v[i].x;
		// y += kombinasi((float)(size - 1), (float)i) * pow((1 - t) * 1.0, (size - i - 1) * 1.0) * pow(t, i) * v[i].y;

		// keep the column consistent~
		x += kombinasi((float)(size - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (size - 1 - i)) * v[i].x;
		y += kombinasi((float)(size - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (size - 1 - i)) * v[i].y;
	}
	return Vector(x, y, 0, 1);
}

void DrawBezier(vector<Vector> v) {
	glBegin(GL_POINTS);

	for (float t = 0; t <= 1; t += 0.0001) {
		Vector calculated_v = get_calculated_bezier_point(v, t);
		glVertex3f(calculated_v.x, calculated_v.y, calculated_v.z);
	}

	glEnd();
}

void DisplayHouse() {
	///// CLEAR /////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	
	// glRotatef(100, 1, 1, 1);

	///// DRAW /////

	// CRESCENT MOON
	Vector c1(-552, 750, 0, 1), c3(-552, 352, 0, 1), c2(-350, 525, 0, 1);
	vector<Vector> v;
	v.push_back(c1);
	v.push_back(c2);
	v.push_back(c3);
	DrawHalfCircle(Vector(-550, 550, 0, 1), 200); // DRAW 1/2 CIRCLE
	DrawBezier(v);
	

	// LINES
	glColor3f(0.1, 0.1, 1);
	glBegin(GL_LINES);
	for (int i = 1; i < points.size(); i += 1) {
		glVertex2f(points[i - 1].x, points[i - 1].y);
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
	// LINES TO BEZIER
	glColor3f(1, 1, 1);
	DrawBezier(points);
	// DRAW PUSHED POINTS
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();

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

void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		float ox = x - WINDOW_SIZE / 2;
		float oy = y - WINDOW_SIZE / 2;
		points.push_back(Vector(ox * 2, -oy * 2, 0, 1));
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		points.clear();
	}
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

	glutMouseFunc(OnMouseClick);

	glutMainLoop();

}