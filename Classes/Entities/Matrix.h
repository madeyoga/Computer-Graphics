#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Vector.h"

class Matrix {
public:

	vector <vector<float>> matrix;
	vector <float> ___vector_m;

	int matrix2[4][4];

	Matrix() {
		matrix = loadMatrix(4, 4, "identity.txt");
	}

	Matrix(bool identity) {
		matrix = loadMatrix(4, 4, "identity.txt");
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
			matrix = Matrix(4, 1).matrix;
			matrix[0][0] = __vector.x;
			matrix[1][0] = __vector.y;
			matrix[2][0] = __vector.z;
			matrix[3][0] = 1;
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

		//// baris 1
		//__matrix_temp.matrix[0][0] = matrix[0][0] * _m.matrix[0][0] + matrix[0][1] * _m.matrix[1][0] + matrix[0][2] * _m.matrix[2][0] + matrix[0][3] * _m.matrix[3][0];
		//__matrix_temp.matrix[0][1] = matrix[0][0] * _m.matrix[0][1] + matrix[0][1] * _m.matrix[1][1] + matrix[0][2] * _m.matrix[2][1] + matrix[0][3] * _m.matrix[3][1];
		//__matrix_temp.matrix[0][2] = matrix[0][0] * _m.matrix[0][2] + matrix[0][1] * _m.matrix[1][2] + matrix[0][2] * _m.matrix[2][2] + matrix[0][3] * _m.matrix[3][2];
		//__matrix_temp.matrix[0][3] = matrix[0][0] * _m.matrix[0][3] + matrix[0][1] * _m.matrix[1][3] + matrix[0][2] * _m.matrix[2][3] + matrix[0][3] * _m.matrix[3][3];

		//// baris 2
		//__matrix_temp.matrix[1][0] = matrix[1][0] * _m.matrix[0][0] + matrix[1][1] * _m.matrix[1][0] + matrix[1][2] * _m.matrix[2][0] + matrix[1][3] * _m.matrix[3][0];
		//__matrix_temp.matrix[1][1] = matrix[1][0] * _m.matrix[0][1] + matrix[1][1] * _m.matrix[1][1] + matrix[1][2] * _m.matrix[2][1] + matrix[1][3] * _m.matrix[3][1];
		//__matrix_temp.matrix[1][2] = matrix[1][0] * _m.matrix[0][2] + matrix[1][1] * _m.matrix[1][2] + matrix[1][2] * _m.matrix[2][2] + matrix[1][3] * _m.matrix[3][2];
		//__matrix_temp.matrix[1][3] = matrix[1][0] * _m.matrix[0][3] + matrix[1][1] * _m.matrix[1][3] + matrix[1][2] * _m.matrix[2][3] + matrix[1][3] * _m.matrix[3][3];

		//// baris 3
		//__matrix_temp.matrix[2][0] = matrix[2][0] * _m.matrix[0][0] + matrix[2][1] * _m.matrix[1][0] + matrix[2][2] * _m.matrix[2][0] + matrix[2][3] * _m.matrix[3][0];
		//__matrix_temp.matrix[2][1] = matrix[2][0] * _m.matrix[0][1] + matrix[2][1] * _m.matrix[1][1] + matrix[2][2] * _m.matrix[2][1] + matrix[2][3] * _m.matrix[3][1];
		//__matrix_temp.matrix[2][2] = matrix[2][0] * _m.matrix[0][2] + matrix[2][1] * _m.matrix[1][2] + matrix[2][2] * _m.matrix[2][2] + matrix[2][3] * _m.matrix[3][2];
		//__matrix_temp.matrix[2][3] = matrix[2][0] * _m.matrix[0][3] + matrix[2][1] * _m.matrix[1][3] + matrix[2][2] * _m.matrix[2][3] + matrix[2][3] * _m.matrix[3][3];

		//// baris 3
		//__matrix_temp.matrix[3][0] = matrix[3][0] * _m.matrix[0][0] + matrix[3][1] * _m.matrix[1][0] + matrix[3][2] * _m.matrix[2][0] + matrix[3][3] * _m.matrix[3][0];
		//__matrix_temp.matrix[3][1] = matrix[3][0] * _m.matrix[0][1] + matrix[3][1] * _m.matrix[1][1] + matrix[3][2] * _m.matrix[2][1] + matrix[3][3] * _m.matrix[3][1];
		//__matrix_temp.matrix[3][2] = matrix[3][0] * _m.matrix[0][2] + matrix[3][1] * _m.matrix[1][2] + matrix[3][2] * _m.matrix[2][2] + matrix[3][3] * _m.matrix[3][2];
		//__matrix_temp.matrix[3][3] = matrix[3][0] * _m.matrix[0][3] + matrix[3][1] * _m.matrix[1][3] + matrix[3][2] * _m.matrix[2][3] + matrix[3][3] * _m.matrix[3][3];

		return __matrix_temp;
	}

	Matrix multiplies(vector<vector<float>> _m) {
		// MATRIX m x p * p x n --> MATRIX m x n
		Matrix __matrix_temp(matrix.size(), _m[0].size());
		// KOLOM MATRIX 1
		for (int i = 0; i < matrix.size(); i++) {
			// KOLOM MATRIX 2
			for (int __count = 0; __count < _m[0].size(); __count++) { // COUNT 
				float temp = 0;
				// KOLOM MATRIX 1 dan BARIS MATRIX 2
				for (int j = 0; j < matrix[0].size(); j++) {
					temp += matrix[i][j] * _m[j][__count];
				}
				__matrix_temp.matrix[i][__count] = temp;
			}
		}

		return __matrix_temp;
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
		Matrix __matrix_temp(/*__temp_vector_m.___vector_m.size()*/ 4, 1);

		for (int i = 0; i < matrix.size(); i++) {
			// MATRIX COLUMNS AND VECTORS ROWS
			for (int j = 0; j < matrix[0].size(); j++) {	
				__matrix_temp.matrix[i][0] += matrix[i][j] * __temp_vector_m.___vector_m[j];
			}
		}

		/*__matrix_temp.matrix[0][0] = matrix[0][0] * __temp_vector_m.___vector_m[0] + matrix[0][1] * __temp_vector_m.___vector_m[1] + matrix[0][2] * __temp_vector_m.___vector_m[2] + matrix[0][3] * __temp_vector_m.___vector_m[3];
	
		__matrix_temp.matrix[1][0] = matrix[1][0] * __temp_vector_m.___vector_m[0] + matrix[1][1] * __temp_vector_m.___vector_m[1] + matrix[1][2] * __temp_vector_m.___vector_m[2] + matrix[1][3] * __temp_vector_m.___vector_m[3];

		__matrix_temp.matrix[2][0] = matrix[2][0] * __temp_vector_m.___vector_m[0] + matrix[2][1] * __temp_vector_m.___vector_m[1] + matrix[2][2] * __temp_vector_m.___vector_m[2] + matrix[2][3] * __temp_vector_m.___vector_m[3];

		__matrix_temp.matrix[3][0] = matrix[3][0] * __temp_vector_m.___vector_m[0] + matrix[3][1] * __temp_vector_m.___vector_m[1] + matrix[3][2] * __temp_vector_m.___vector_m[2] + matrix[3][3] * __temp_vector_m.___vector_m[3];
*/

		// CONVERTS MATRIX TO VECTOR 
		/*float x = __matrix_temp.matrix[0][0];
		float y = __matrix_temp.matrix[1][0];
		float z = __matrix_temp.matrix[2][0];*/
		/*if (__matrix_temp.matrix.size() == 4)
			w = 1;*/

		// Vector _v(x, y, z, 1);

		return Vector(__matrix_temp.matrix[0][0], __matrix_temp.matrix[1][0], __matrix_temp.matrix[2][0], 1);
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

	Matrix translates(Vector __vector) {
		// return multiplies(__vector);
		Matrix _matrix;
		_matrix.matrix[0][3] = __vector.x;
		_matrix.matrix[1][3] = __vector.y;
		_matrix.matrix[2][3] = __vector.z;
		_matrix.matrix[3][3] = 1;
		return _matrix;
	}

	Vector scales(Vector _vector) {
		return multiplies(_vector);
	}
	
	void insert_rotation_x(float _angle_theta) {

		// matrix = loadMatrix(4, 4, "identity.txt");
		matrix[1][1] = cos(_angle_theta);
		matrix[1][2] = -sin(_angle_theta);
		matrix[2][1] = sin(_angle_theta);
		matrix[2][2] = cos(_angle_theta);

	}

	void insert_rotation_y(float _angle_theta) {

		// matrix = loadMatrix(4, 4, "identity.txt");
		matrix[0][0] = cos(_angle_theta);
		matrix[0][2] = sin(_angle_theta);
		matrix[2][0] = -sin(_angle_theta);
		matrix[2][2] = cos(_angle_theta);

	}

	void insert_rotation_z(float _angle_theta) {

		// matrix = loadMatrix(4, 4, "identity.txt");
		matrix[0][0] = cos(_angle_theta);
		matrix[0][1] = -sin(_angle_theta);
		matrix[1][0] = sin(_angle_theta);
		matrix[1][1] = cos(_angle_theta);

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