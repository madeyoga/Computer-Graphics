// #include "Vector.h"
#include <iostream>
#include <vector>
using namespace std;

#include "GL Libraries\GL\glut.h"
#include "Vector.h"

#define WINDOW_SIZE 800

vector <Vector> points;

vector <Vector> cloud_vector[10];

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
	glPointSize(1.5); //ukuran titik/point

	for (float i = 1; i < 5; i += 0.0001)
	{
		float x = point.x + cos(i) * radius;
		float y = point.y + sin(i) * radius;

		glBegin(GL_POINTS);
		glVertex3f(x, y, 0);
		glEnd();
	}
}

void DrawCircle(Vector point, int radius) {
	glBegin(GL_POINTS);
	glPointSize(0.5); //ukuran titik/point

	for (float i = -3.14; i < 3.14; i += 0.0001)
	{
		float x = point.x + cos(i) * radius;
		float y = point.y + sin(i) * radius;
		glVertex3f(x, y, 0);
	}
	glEnd();
}

void DrawCircle(Vector point, float r_x, float r_y)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(point.x, point.y);
	for (int i = 0; i <= 360; i++) {
		float x = point.x + cos(i) * r_x;
		float y = point.y + sin(i) * r_y;
		glVertex2f(x, y);
	}
	glEnd();
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

void DrawBezier(vector<Vector> v[]) {
	glBegin(GL_POINTS);
	for (int i = 0; i < 6; i++) {
		for (float t = 0; t <= 1; t += 0.0001) {
			Vector calculated_v = get_calculated_bezier_point(v[i], t);
			glVertex3f(calculated_v.x, calculated_v.y, calculated_v.z);
		}
	}
	glEnd();
}

void drawCloud(const Vector pos) {
	int x = pos.x, y = pos.y;

	DrawCircle(Vector(x, y, 0, 1), 80, 45);
	DrawCircle(Vector(x + 25, y + 15, 0, 1), 35, 35);
	DrawCircle(Vector(x + 25, y - 15, 0, 1), 35, 35);
	DrawCircle(Vector(x - 25, y - 15, 0, 1), 35, 35);
	DrawCircle(Vector(x - 25, y + 15, 0, 1), 35, 35);
}

void DisplayHouse() {
	///// CLEAR /////
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	
	// glRotatef(100, 1, 1, 1);

	///// DRAW /////

	// TUGAS EXCEL 
	Vector p1(0, 1, 0, 1), p2(1, 2, 0, 1), p3(2, 2, 0, 1), p4(3, 1, 0, 1);
	vector<Vector>excel_point;
	excel_point.push_back(p1 * 100);
	excel_point.push_back(p2 * 100);
	excel_point.push_back(p3 * 100);
	excel_point.push_back(p4 * 100);
	DrawBezier(excel_point);

	// CRESCENT MOON
	Vector c1(-442, 718, 0, 1), c3(-496, 360, 0, 1), c2(-688, 584, 0, 1);
	vector<Vector> v;
	v.push_back(c1);
	v.push_back(c2);
	v.push_back(c3);
	DrawHalfCircle(Vector(-550, 550, 0, 1), 200); // DRAW 1/2 CIRCLE
	DrawBezier(v);
	

	// Cloud
	// DrawBezier(cloud_vector);
	drawCloud(Vector(500, 600, 0, 1));
	drawCloud(Vector(400, 600, 0, 1));

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
		cout << ox * 2 << " : " << -oy * 2 << endl;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		points.clear();
	}
}

void main(int argc, char **argv) {

	// OLD CLOUD USING BEZIER
	// CLOUD VECTOR VALUES
	/*Vector v1 (252, 644, 0, 1), v2 (380, 724, 0, 1), v3 (496, 648, 0, 1),
		   v4 (496, 648, 0, 1), v5 (578, 684, 0, 1), v6 (642, 640, 0, 1),
		   v7 (252, 646, 0, 1), v8 (128, 624, 0, 1), v9 (148, 532, 0, 1),
		   v10(644, 638, 0, 1), v11(706, 572, 0, 1), v12(604, 512, 0, 1),
		   v13(148, 530, 0, 1), v14(150, 476, 0, 1), v15(230, 484, 0, 1), v16(248, 507, 0, 1);

	cloud_vector[0].push_back(v1);
	cloud_vector[0].push_back(v2);
	cloud_vector[0].push_back(v3);

	cloud_vector[1].push_back(v4);
	cloud_vector[1].push_back(v5);
	cloud_vector[1].push_back(v6);

	cloud_vector[2].push_back(v7);
	cloud_vector[2].push_back(v8);
	cloud_vector[2].push_back(v9);

	cloud_vector[3].push_back(v10);
	cloud_vector[3].push_back(v11);
	cloud_vector[3].push_back(v12);

	cloud_vector[4].push_back(v13);
	cloud_vector[4].push_back(v14);
	cloud_vector[4].push_back(v15);
	cloud_vector[4].push_back(v16);
	
	cloud_vector[5].push_back(Vector(248, 508, 0, 1));
	cloud_vector[5].push_back(Vector(300, 362, 0, 1));
	cloud_vector[5].push_back(Vector(370, 612, 0, 1));
	cloud_vector[5].push_back(Vector(466, 350, 0, 1));
	cloud_vector[5].push_back(Vector(602, 514, 0, 1));*/

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