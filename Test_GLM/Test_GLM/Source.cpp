
#include "Vector.h"
#include "Matrix.h"
#include "Matrix2.h"
#include "Quadric.h"
#include "Hirearchy.h"
#include "GL Libraries\GL\glut.h"

#define WINDOW_SIZE 500

// Quadric __bola, __elips;
Hirearchy __solar_system[3];



void idle() {
	glutPostRedisplay();
}

void initCanvas() {
	// INIT CANVAS
	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);
	
	// CLEAR
	glClearColor(0, 0, 0, 0);

	float col[3] = { 255, 255, 255 };

	Matrix2 _sun_transform, _earth_transform, _moon_transform;
	_sun_transform.translate(Vector(0, 0, 0, 1));
	_earth_transform.translate(Vector(200, 0, 0, 1));
	_moon_transform.translate(Vector(75, 0, 0, 1));

	Quadric _sun, _moon, _earth;
	_sun.ball(100);
	_earth.ball(50);
	_moon.ball(20);

	__solar_system[0].set_quadric(_sun);
	__solar_system[0].set_index(-1); // -1 ketentuan parent
	__solar_system[0].set_matrix_transformation(_sun_transform);
	
	__solar_system[1].set_quadric(_earth);
	__solar_system[1].set_index(0);
	__solar_system[1].set_matrix_transformation(_earth_transform);
	
	__solar_system[2].set_quadric(_moon);
	__solar_system[2].set_index(1);
	__solar_system[2].set_matrix_transformation(_moon_transform);

}

float theta = 0;
void test() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (theta >= 360) {
		theta = 0;
	}
	theta += 0.01;

	__solar_system[0]._matrix_transformation2.rotate_z(theta);
	__solar_system[1]._matrix_transformation2.rotate_z(theta);
	__solar_system[2]._matrix_transformation2.rotate_z(theta);
	
	 for (int i = 0; i < 3; i++) {
		__solar_system[i].draw2(__solar_system);
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
