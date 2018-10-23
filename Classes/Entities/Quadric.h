#pragma once

#define phi 3.14159

class Quadric {
	
public:

	Vector __m_titik[100][50];
	float row, col; // kerapatan stiap titik.

	Quadric() {
		row = 45;
		col = 45;
	}

	void ball(int r) {
		int __i = 0;
		int __j = 0;
		for (float i = -phi; i <= phi; i += 2 * phi / row) {
			__j = 0;
			for (float j = -phi; j <= phi; j += 2 * phi / col) {
				__m_titik[__i][__j].set_value(r * cos(i) * cos(j), r * cos(i)*sin(j), r * sin(i));
				__j++;
			}
			__i++;
		}
	}

	void tube(int r) {
		int __i = 0;
		int __j = 0;
		for (float i = -100; i <= 100; i += 200 / row) {
			__j = 0;
			for (float j = -phi; j <= phi; j += 2 * phi / col) {
				__m_titik[__i][__j].set_value(r*cos(j), r*sin(j), i);
				__j++;
			}
			__i++;
		}
	}

	void elipse(int r, int b) {
		int __i = 0;
		int __j = 0;
		for (float i = -phi; i <= phi; i += 2 * phi / row) {
			__j = 0;
			for (float j = -phi; j <= phi; j += 2 * phi / col) {
				__m_titik[__i][__j].set_value(r * cos(i) * cos(j), b * cos(i)*sin(j), r * sin(i));
				__j++;
			}
			__i++;
		}
	}

	void hyperbola(int r, int b) {
		int __i = 0;
		int __j = 0;
		for (float i = -phi; i <= phi; i += 2 * phi / row) {
			__j = 0;
			for (float j = -phi; j <= phi; j += 2 * phi / col) {
				__m_titik[__i][__j].set_value(b * cos(i) * cos(j), r * cos(i)*sin(j), b * sin(i));
				__j++;
			}
			__i++;
		}
	}

	void draw_wire() {
		// VERTICAL
		for (int i = 1; i < row; i++) {
			for (int j = 0; j < col; j++) {
				glColor3f(0, 0.5, 1);
				glBegin(GL_LINES);
				glVertex3f(__m_titik[i][j].x, __m_titik[i][j].y, __m_titik[i][j].z);
				glVertex3f(__m_titik[i - 1][j].x, __m_titik[i - 1][j].y, __m_titik[i - 1][j].z);
				glEnd();
			}
		}
		// HORIZONTAL
		for (int i = 0; i < row; i++) {
			for (int j = 1; j < col; j++) {
				glColor3f(0, 1, 0.5);
				glBegin(GL_LINES);
				glVertex3f(__m_titik[i][j].x, __m_titik[i][j].y, __m_titik[i][j].z);
				glVertex3f(__m_titik[i][j - 1].x, __m_titik[i][j - 1].y, __m_titik[i][j - 1].z);
				glEnd();
			}
		}
	}

};