#pragma once

#include "Vector.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Matrix2 {
public:
	float _matrix[4][4];
	int _i, _j;

	Matrix2() {
		_i = 4;
		_j = 4;
		loadMatrix(4, 4, "identity.txt");
	}
	Matrix2(int  __i , int __j) {
		for (int i = 0; i < __i; i++) {
			for (int j = 0; j < __j; j++) {
				_matrix[i][j] = 0;
			}
		}
		_i = __i;
		_j = __j;
	}
	Matrix2(Vector __vector) {
		_matrix[0][0] = __vector.x;
		_matrix[1][0] = __vector.y;
		_matrix[2][0] = __vector.z;
		_matrix[3][0] = __vector.w;
	}

	void loadMatrix(int __i, int __j, std::string __filename) {
		ifstream in(__filename);

		if (!in) {
			cout << "Cannot open file.\n";
			return;
		}

		for (int i = 0; i < __i; i++) {
			for (int j = 0; j < __j; j++) {
				float temp;
				in >> temp;
				_matrix[i][j] = temp;
				if (in.eof()) { break; }
			}
			if (in.eof()) { break; }
		}

		if (!in.eof()) {
			cout << "Not a valid matrix size!" << endl
				<< "loads " << __i << "*" << __j << " matrix" << endl;
		}

		in.close();

	}

	Vector multiplies(Vector __vector) {
		Matrix2 _vector_m(__vector);
		Matrix2 _temp(4, 1);
		for (int i = 0; i < _i; i++) {
			for (int j = 0; j < _j; j++) {
				_temp._matrix[i][0] += _matrix[i][j] * _vector_m._matrix[j][0];
			}
		}
		float x = _temp._matrix[0][0];
		float y = _temp._matrix[1][0];
		float z = _temp._matrix[2][0];
		float w = 1 /*_temp._matrix[3][0]*/;
		return Vector(x, y, z, w);
	}

	Matrix2 multiplies(Matrix2 __m) {
		Matrix2 __matrix_temp(_i, __m._j);
		// BARIS MATRIX 1
		for (int i = 0; i < _i; i++) {
			// KOLOM MATRIX 2
			for (int __count = 0; __count < __m._j; __count++) { // COUNT 
				float temp = 0;
				// KOLOM MATRIX 1 dan BARIS MATRIX 2
				for (int j = 0; j < _j; j++) {
					temp += _matrix[i][j] * __m._matrix[j][__count];
				}
				__matrix_temp._matrix[i][__count] = temp;
			}
		}
		return __matrix_temp;
	}

	void rotate(float _angle_theta, int x, int y, int z) {
		Matrix2 _matrix_temp;
		Matrix2 _m_t_rx;
		Matrix2 _m_t_ry;
		Matrix2 _m_t_rz;
		bool attempt = false;
		if (x > 0) {
			_m_t_rx.rotate_x(_angle_theta);
			_matrix_temp = _m_t_rx;
			attempt = true;
		} 
		if (y > 0) {
			_m_t_ry.rotate_y(_angle_theta);
			if (attempt)
				_matrix_temp = _matrix_temp.multiplies(_m_t_ry);
			else 
				_matrix_temp = _m_t_ry;
		}
		if (z > 0) {
			_m_t_rz.rotate_z(_angle_theta);
			if (attempt)
				_matrix_temp = _matrix_temp.multiplies(_m_t_rz);
			else 
				_matrix_temp = _m_t_rz;
		}
		(*this) = _matrix_temp;
	}

	void rotate_x(float _angle_theta){
		_matrix[1][1] = cos(_angle_theta);
		_matrix[1][2] = -sin(_angle_theta);
		_matrix[2][1] = sin(_angle_theta);
		_matrix[2][2] = cos(_angle_theta);
	}

	void rotate_y(float _angle_theta) {
		_matrix[0][0] = cos(_angle_theta);
		_matrix[0][2] = sin(_angle_theta);
		_matrix[2][0] = -sin(_angle_theta);
		_matrix[2][2] = cos(_angle_theta);
	}

	void rotate_z(float _angle_theta) {
		_matrix[0][0] = cos(_angle_theta);
		_matrix[0][1] = -sin(_angle_theta);
		_matrix[1][0] = sin(_angle_theta);
		_matrix[1][1] = cos(_angle_theta);
	}

	void translate(Vector __vector) {
		_matrix[0][3] = __vector.x;
		_matrix[1][3] = __vector.y;
		_matrix[2][3] = __vector.z;
		_matrix[3][3] = 1;
	}

	void showMatrixOnConsole() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << _matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

};