#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Vector.h"


/*
 * To Do List:
 * Scalar(V), VECTOR_PRODUCT(V), TRANSLATION, SCALING, ROTATION
 */


class Matrix {
public:

	vector <vector<float>> matrix;
	vector <float> ___vector_m;

	Matrix() {

	}

	Matrix(bool identity) {
		matrix = loadMatrix(4, 4, "identity.txt");
	}



	Matrix(int mode, Vector __vector) {
		if (mode == 0) 
			matrix = loadMatrix(4, 4, "identity.txt");
		else if (mode == 1) { // TRANSLATE
			matrix = loadMatrix(4, 4, "identity.txt");
			matrix[0][matrix[0].size() - 1] = __vector.x;
			matrix[1][matrix[0].size() - 1] = __vector.y;
			matrix[2][matrix[0].size() - 1] = __vector.z;
			matrix[3][matrix[0].size() - 1] = __vector.w;
		}
		else if (mode == 2) { // SCALE
			
		}
		else if (mode == 3) { // TRANSLATE && SCALE

		}
	}

	Matrix(vector <vector<float>> __matrix) {
		matrix = __matrix;
	}

	Matrix(Vector __vector, bool identity = false) {
		if (!identity) {
			___vector_m.push_back(__vector.x);
			___vector_m.push_back(__vector.y);
			___vector_m.push_back(__vector.z);
			___vector_m.push_back(__vector.w);
		}
		else {
			matrix = loadMatrix(4, 4, "identity.txt");
			matrix[0][matrix[0].size() - 1] = __vector.x;
			matrix[1][matrix[0].size() - 1] = __vector.y;
			matrix[2][matrix[0].size() - 1] = __vector.z;
			matrix[3][matrix[0].size() - 1] = __vector.w;
		}
	}

	Matrix(int _i, int _j) {
		for (int i = 0; i < _i; i++) {
			vector <float> __vector;
			for (int j = 0; j < _j; j++) {
				__vector.push_back(0);
			}
			matrix.push_back(__vector);
		}
	}

	Matrix(std::string _filepath, int _i, int _j) {
		matrix = loadMatrix(_i, _j, _filepath);
	}

	std::vector<std::vector<float>> loadMatrix(int __i, int __j, std::string __filename) {
		ifstream in(__filename);
		std::vector<std::vector<float>> _vector;

		if (!in) {
			cout << "Cannot open file.\n";
			return _vector;
		}

		for (int i = 0; i < __i; i++) {
			std::vector <float> __vector_j;
			for (int j = 0; j < __j; j++) {
				float temp;
				in >> temp;
				__vector_j.push_back(temp);
				if (in.eof()) { break; }
			}
			_vector.push_back(__vector_j);
			if (in.eof()) { break; }
		}

		if (!in.eof()) {
			cout << "Not a valid matrix size!" << endl
				 << "loads " << __i << "*" << __j << " matrix" << endl;
		}

		in.close();

		return _vector;
	}

	Matrix plus(Matrix _m) {
		if (_m.matrix.size() != matrix.size() || _m.matrix[0].size() != matrix[0].size()) {
			return (*this);
		}
		std::vector <std::vector<float>> _vector;
		for (int i = 0; i < matrix.size(); i++) {
			std::vector<float> __vector2;
			for (int j = 0; j < _m.matrix.size(); j++) {
				float temp = matrix[i][j] + _m.matrix[i][j];
				__vector2.push_back(temp);
			}
			_vector.push_back(__vector2);
		}
		return Matrix(_vector);
	}
	
	Matrix subtracts(Matrix _m) {
		if (_m.matrix.size() != matrix.size() || _m.matrix[0].size() != matrix[0].size()) {
			return (*this);
		}
		std::vector <std::vector<float>> _vector;
		for (int i = 0; i < matrix.size(); i++) {
			std::vector<float> __vector2;
			for (int j = 0; j < _m.matrix.size(); j++) {
				float temp = matrix[i][j] - _m.matrix[i][j];
				__vector2.push_back(temp);
			}
			_vector.push_back(__vector2);
		}
		return Matrix(_vector);
	}

	Matrix multiplies(Matrix _m) {
		if (matrix[0].size() == _m.matrix.size()) {
			// MATRIX m x p * p x n --> MATRIX m x n
			Matrix __matrix_temp(matrix.size(), _m.matrix[0].size());

			// KOLOM MATRIX 1
			for (int i = 0; i < matrix.size(); i++) {
				// KOLOM MATRIX 2
				for (int __count = 0; __count < _m.matrix[0].size(); __count++) { // COUNT 
					float temp = 0;
					// KOLOM MATRIX 1 dan BARIS MATRIX 2
					for (int j = 0; j < matrix[0].size(); j++) {
						temp += matrix[i][j] * _m.matrix[j][__count];
					}
					__matrix_temp.matrix[i][__count] = temp;
				}

			}

			return __matrix_temp;
		}
		else {
			return (*this);
		}
	}

	Matrix multiplies(float __scalar) {
		Matrix __temp_matrix(matrix.size(), matrix[0].size());
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				__temp_matrix.matrix[i][j] = matrix[i][j] * __scalar;
			}
		}
		return __temp_matrix;
	}

	Vector multiplies(Vector __vector) {
		// TEMP MATRIX FROM GIVEN VECTOR
		Matrix __temp_vector_m(__vector);

		// TEMP RESULT FOR A NEW VECTOR
		Matrix __matrix_temp(__temp_vector_m.___vector_m.size(), 1);

		// TEMP RESULT MATRIX ROW INDEX
		int index_ = 0;

		for (int i = 0; i < matrix.size(); i++) {
			// MATRIX COLUMNS AND VECTORS ROWS
			for (int j = 0; j < matrix[0].size(); j++) {	
				__matrix_temp.matrix[index_][0] += matrix[i][j] * __temp_vector_m.___vector_m[j];
			}
			index_++;
		}

		// CONVERTS MATRIX TO VECTOR 
		float x = __matrix_temp.matrix[0][0];
		float y = __matrix_temp.matrix[1][0];
		float z = __matrix_temp.matrix[2][0];
		float w = 1;
		if (__matrix_temp.matrix.size() == 4)
			w = __matrix_temp.matrix[3][0];

		Vector _v(x, y, z, w);

		return _v;
	}

	void insert_translate(Vector __vector) {
		matrix[0][matrix[0].size() - 1] = __vector.x;
		matrix[1][matrix[0].size() - 1] = __vector.y;
		matrix[2][matrix[0].size() - 1] = __vector.z;
		matrix[3][matrix[0].size() - 1] = __vector.w;
	}

	void insert_scale(Vector __vector) {
		matrix[0][0] = __vector.x;
		matrix[1][1] = __vector.y;
		matrix[2][2] = __vector.z;
		matrix[3][3] = __vector.w;
	}

	Vector translates(Vector _v) {
		return multiplies(_v);
	}

	Vector scales(Vector _v) {
		return multiplies(_v);
	}

	void loadRotationsX(float _angle_theta) {

		matrix = loadMatrix(4, 4, "identity.txt");
		matrix[1][1] = cos(_angle_theta);
		matrix[1][2] = -sin(_angle_theta);
		matrix[2][1] = sin(_angle_theta);
		matrix[2][2] = cos(_angle_theta);

	}

	Vector rotates(float _angle_theta, int _x, int _y, int _z, Vector _v) {
		Vector _v_x(1, 1, 1, 1), _v_y(1, 1, 1, 1), _v_z(1, 1, 1, 1);
		if (_x >= 1) {
			Matrix _matrix_rotation_x(true);
			_matrix_rotation_x.matrix[1][1] = cos(_angle_theta);
			_matrix_rotation_x.matrix[1][2] = -sin(_angle_theta);
			_matrix_rotation_x.matrix[2][1] = sin(_angle_theta);
			_matrix_rotation_x.matrix[2][2] = cos(_angle_theta);
			_v_x = _matrix_rotation_x.multiplies(_v);
		}
		if (_y >= 1) {
			Matrix _matrix_rotation_y(true);
			_matrix_rotation_y.matrix[0][0] = cos(_angle_theta);
			_matrix_rotation_y.matrix[0][2] = sin(_angle_theta);
			_matrix_rotation_y.matrix[2][0] = -sin(_angle_theta);
			_matrix_rotation_y.matrix[2][2] = cos(_angle_theta);
			_v_y = _matrix_rotation_y.multiplies(_v);
		}
		if (_z >= 1) {
			Matrix _matrix_rotation_z(true);
			_matrix_rotation_z.matrix[0][0] = cos(_angle_theta);
			_matrix_rotation_z.matrix[0][1] = -sin(_angle_theta);
			_matrix_rotation_z.matrix[1][0] = sin(_angle_theta);
			_matrix_rotation_z.matrix[1][1] = cos(_angle_theta);
			_v_z = _matrix_rotation_z.multiplies(_v);
		}
		Vector __vector = _v_x * _v_y * _v_z;
		return __vector;
	}

	Vector rotates_x_axis(float _angle_theta, Vector v) {
		Matrix _matrix_rotation_x(true);
		_matrix_rotation_x.matrix[1][1] = cos(_angle_theta);
		_matrix_rotation_x.matrix[1][2] = -sin(_angle_theta);
		_matrix_rotation_x.matrix[2][1] = sin(_angle_theta);
		_matrix_rotation_x.matrix[2][2] = cos(_angle_theta);
		return _matrix_rotation_x.multiplies(v);
	}

	Vector rotates_y_axis(float _angle_theta, Vector v) {
		Matrix _matrix_rotation_y(true);
		_matrix_rotation_y.matrix[0][0] = cos(_angle_theta);
		_matrix_rotation_y.matrix[0][2] = sin(_angle_theta);
		_matrix_rotation_y.matrix[2][0] = -sin(_angle_theta);
		_matrix_rotation_y.matrix[2][2] = cos(_angle_theta);
		return _matrix_rotation_y.multiplies(v);
	}

	Vector rotates_z_axis(float _angle_theta, Vector v) {
		Matrix _matrix_rotation_z(true);
		_matrix_rotation_z.matrix[0][0] = cos(_angle_theta);
		_matrix_rotation_z.matrix[0][1] = -sin(_angle_theta);
		_matrix_rotation_z.matrix[1][0] = sin(_angle_theta);
		_matrix_rotation_z.matrix[1][1] = cos(_angle_theta);
		 return _matrix_rotation_z.multiplies(v);
	}
	
	Vector transforms(Vector _v) {
		return multiplies(_v);
	}

	Matrix operator+ (Matrix _m) {
		return plus(_m);
	}

	Matrix operator- (Matrix _m) {
		return subtracts(_m);
	}

	Matrix operator* (Matrix _m) {
		return multiplies(_m);
	}

	Matrix operator* (float __scalar) {
		return multiplies(__scalar);
	}

	Vector operator* (Vector _vector) {
		return multiplies(_vector);
	}

	void showMatrixOnConsole() {
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

};

Matrix operator* (float __scalar, Matrix __m) {
	return __m.multiplies(__scalar);
}

Vector rotates_x_axis(float _angle_theta, Vector v) {
	Matrix _matrix_rotation_x(true);
	_matrix_rotation_x.matrix[1][1] = cos(_angle_theta);
	_matrix_rotation_x.matrix[1][2] = -sin(_angle_theta);
	_matrix_rotation_x.matrix[2][1] = sin(_angle_theta);
	_matrix_rotation_x.matrix[2][2] = cos(_angle_theta);
	return _matrix_rotation_x.multiplies(v);
}

Vector rotates_y_axis(float _angle_theta, Vector v) {
	Matrix _matrix_rotation_y(true);
	_matrix_rotation_y.matrix[0][0] = cos(_angle_theta);
	_matrix_rotation_y.matrix[0][2] = sin(_angle_theta);
	_matrix_rotation_y.matrix[2][0] = -sin(_angle_theta);
	_matrix_rotation_y.matrix[2][2] = cos(_angle_theta);
	return _matrix_rotation_y.multiplies(v);
}

Vector rotates_z_axis(float _angle_theta, Vector v) {
	Matrix _matrix_rotation_z(true);
	_matrix_rotation_z.matrix[0][0] = cos(_angle_theta);
	_matrix_rotation_z.matrix[0][1] = -sin(_angle_theta);
	_matrix_rotation_z.matrix[1][0] = sin(_angle_theta);
	_matrix_rotation_z.matrix[1][1] = cos(_angle_theta);
	return _matrix_rotation_z.multiplies(v);
}