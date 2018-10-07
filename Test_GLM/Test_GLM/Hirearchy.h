#pragma once

#include "Matrix.h"
#include "Quadric.h"

class Hirearchy {
	Quadric _quadric;
	// Matrix transform_temp;
	// Matrix _translasi, rotate, transform;
	int _index; // INDEX PARENT
	Hirearchy *__hirearchy;
public:
	Matrix _matrix_transformation;
	Matrix2 _matrix_transformation2;

	Hirearchy() {
		// _matrix_transformation = Matrix("identity.txt", 4, 4);
	}

	void set_quadric(Quadric __quadric) {
		_quadric = __quadric;
	}

	Quadric get_quadric() {
		return _quadric;
	}

	void set_index(int __index) {
		_index = __index;
	}

	int get_parents_index() {
		return _index;
	}

	void set_matrix_transformation(Matrix _m) {
		_matrix_transformation = _matrix_transformation.multiplies(_m);
	}
	
	void set_matrix_transformation(Matrix2 _m) {
		_matrix_transformation2 = _matrix_transformation2.multiplies(_m);
	}

	Matrix get_transform(Hirearchy *__hirearchy) {
		Matrix __temp;
		if (_index != -1) {
			__temp = __hirearchy[_index].get_transform(__hirearchy);
		}
		__temp = __temp.multiplies(_matrix_transformation.matrix);
		// __temp.showMatrixOnConsole(); //////////////////////////
		return __temp;
	}

	Matrix2 get_transform2(Hirearchy *__hirearchy) {
		Matrix2 __temp;
		if (_index != -1) {
			__temp = __hirearchy[_index].get_transform2(__hirearchy);
		}
		__temp = __temp.multiplies(_matrix_transformation2);
		// __temp.showMatrixOnConsole(); //////////////////////////
		return __temp;
	}

	void draw(Hirearchy *__hirearchy/*, float *__color*/) {
		Vector __dummy[100][50];
		Matrix __temp = get_transform(__hirearchy);
		int r = _quadric.row;
		int c = _quadric.col;
		// __temp.showMatrixOnConsole();
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				__dummy[i][j] = _quadric.__m_titik[i][j];
				__dummy[i][j] = __temp.multiplies(__dummy[i][j]);
				// __dummy[i][j].showVectorOnConsole();
			}
		}

		// glColor3f(__color[0], __color[1], __color[2]);

		glBegin(GL_LINES);
		glColor3f(0, 0.5, 1);
		// VERTICAL
		for (int i = 1; i < r; i++) {
			for (int j = 0; j < c; j++) {
				glVertex3f(__dummy[i][j].x, __dummy[i][j].y, __dummy[i][j].z);
				glVertex3f(__dummy[i - 1][j].x, __dummy[i - 1][j].y, __dummy[i - 1][j].z);
			}
		}

		glColor3f(0, 1, 0.5);
		// HORIZONTAL
		for (int i = 0; i < r; i++) {
			for (int j = 1; j < c; j++) {
				glVertex3f(__dummy[i][j].x, __dummy[i][j].y, __dummy[i][j].z);
				glVertex3f(__dummy[i][j - 1].x, __dummy[i][j - 1].y, __dummy[i][j - 1].z);
			}
		}
		glEnd();
	}

	void draw2(Hirearchy *__hirearchy/*, float *__color*/) {
		Vector __dummy[100][50];
		Matrix2 __temp = get_transform2(__hirearchy);
		int r = _quadric.row;
		int c = _quadric.col;
		// __temp.showMatrixOnConsole();
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				__dummy[i][j] = _quadric.__m_titik[i][j];
				__dummy[i][j] = __temp.multiplies(__dummy[i][j]);
				// __dummy[i][j].showVectorOnConsole();
			}
		}

		// glColor3f(__color[0], __color[1], __color[2]);

		glBegin(GL_LINES);
		glColor3f(0, 0.5, 1);
		// VERTICAL
		for (int i = 1; i < r; i++) {
			for (int j = 0; j < c; j++) {
				glVertex3f(__dummy[i][j].x, __dummy[i][j].y, __dummy[i][j].z);
				glVertex3f(__dummy[i - 1][j].x, __dummy[i - 1][j].y, __dummy[i - 1][j].z);
			}
		}

		glColor3f(0, 1, 0.5);
		// HORIZONTAL
		for (int i = 0; i < r; i++) {
			for (int j = 1; j < c; j++) {
				glVertex3f(__dummy[i][j].x, __dummy[i][j].y, __dummy[i][j].z);
				glVertex3f(__dummy[i][j - 1].x, __dummy[i][j - 1].y, __dummy[i][j - 1].z);
			}
		}
		glEnd();
	}

};