
#include "Vector.h"
#include "Matrix.h"
#include "Matrix2.h"
#include "Quadric.h"
#include "Hirearchy.h"
#include "GL Libraries\GL\glut.h"

#define WINDOW_SIZE 500

Hirearchy __solar_system[3];
Hirearchy __kipas_system[3];
void idle() {
	glutPostRedisplay();
}

void initCanvas() {
	// INIT CANVAS
	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);
	
	// CLEAR
	glClearColor(0, 0, 0, 0);

	float white[3] = { 255, 255, 255 };
	float orange[3] = { 255, 128, 0 };
	
	Matrix2 _badan_transform, _leher_transform;
	_badan_transform.translate(Vector(10, 0, 0, 1));
	_leher_transform.translate(Vector(50, 0, 0, 1));

	Quadric _badan_kipas, _leher_kipas;
	_badan_kipas.elipse(20, 50);
	_leher_kipas.elipse(20, 50);

	__kipas_system[0].set_quadric(_badan_kipas);
	__kipas_system[0].set_color(orange);
	__kipas_system[0].set_index(-1);
	__kipas_system[0].set_matrix_transformation(_badan_transform);

	__kipas_system[1].set_quadric(_leher_kipas);
	__kipas_system[1].set_color(white);
	__kipas_system[1].set_index(0);
	__kipas_system[1].set_matrix_transformation(_leher_transform);

	//Matrix2 _sun_transform, _earth_transform, _moon_transform;
	//_sun_transform.translate(Vector(0, 0, 0, 1));
	//_earth_transform.translate(Vector(200, 0, 0, 1));
	//_moon_transform.translate(Vector(75, 0, 0, 1));

	//Quadric _sun, _moon, _earth;
	//_sun.ball(100);
	//_earth.ball(50);
	//_moon.ball(20);

	//__solar_system[0].set_quadric(_sun);
	//__solar_system[0].set_index(-1); // -1 ketentuan parent
	//__solar_system[0].set_matrix_transformation(_sun_transform);
	//
	//__solar_system[1].set_quadric(_earth);
	//__solar_system[1].set_index(0);
	//__solar_system[1].set_matrix_transformation(_earth_transform);
	//
	//__solar_system[2].set_quadric(_moon);
	//__solar_system[2].set_index(1);
	//__solar_system[2].set_matrix_transformation(_moon_transform);

}

float theta = 0;
void test() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (theta >= 360) {
		theta = 0;
	}
	theta += 0.01;

	// glRotatef(1, 1, 1, 1);
	__solar_system[0]._matrix_transformation2.rotate_z(theta);
	// __solar_system[0]._matrix_transformation2.rotate(theta, 0, 0, 1);
	__solar_system[1]._matrix_transformation2.rotate_z(theta);
	__solar_system[2]._matrix_transformation2.rotate_z(theta);
	
	glColor3f(1, 0.5, 0);

	 for (int i = 1; i < 3; i++) {
		__kipas_system[i].draw2(__kipas_system);
	 }

	glutSwapBuffers();
}

void main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Bezier & Rumah");
	
	glutIdleFunc(idle);

	glutDisplayFunc(test);

	initCanvas();

	glutMainLoop();


}
