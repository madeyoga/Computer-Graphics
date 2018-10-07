#pragma once
#include <iostream>
#include "Vector.h"
using namespace std;

#define MATRIX_MAX_SIZE 8

class Matrix {
private:
	int** matrix;
	int I_MAX;
	int J_MAX;
public:

	Matrix(int _i, int _j) {
		I_MAX = _i;
		J_MAX = _j;

		// CREATING ARRAY2D
		matrix = 0;
		matrix = new int*[MATRIX_MAX_SIZE];
		for (int i = 0; i < MATRIX_MAX_SIZE; i++) {
			matrix[i] = new int[MATRIX_MAX_SIZE];
			for (int j = 0; j < MATRIX_MAX_SIZE; j++) {
				matrix[i][j] = 0;
			}
		}
		matrix[0][0] = 3;
		matrix[0][1] = 0;
		matrix[0][2] = 2;

		matrix[1][0] = 2;
		matrix[1][1] = 0;
		matrix[1][2] = -2;

		matrix[2][0] = 0;
		matrix[2][1] = 1;
		matrix[2][2] = 1;
	}

	int** get2DValue() {
		return matrix;
	}

	int getValueAt(int i, int j) {
		return matrix[i][j];
	}

	void setValueAt(int i, int j, int value) {
		matrix[i][j] = value;
	}

	Matrix operator*(int val) {
		for (int i = 0; i < I_MAX; i++) {
			for (int j = 0; j < J_MAX; j++) {
				matrix[i][j] *= val;
			}
		}
		return (*this);
	}

	Matrix operator+(Matrix _matrix) {
		if (_matrix.getMaxI() != I_MAX || _matrix.getMaxJ() != J_MAX)
			return (*this);

		for (int i = 0; i < I_MAX; i++) {
			for (int j = 0; j < J_MAX; j++) {
				matrix[i][j] += _matrix.getValueAt(i, j);
			}
		}

		return (*this);
	}

	Matrix operator-(Matrix _matrix) {
		if (_matrix.getMaxI() != I_MAX || _matrix.getMaxJ() != J_MAX)
			return (*this);

		for (int i = 0; i < I_MAX; i++) {
			for (int j = 0; j < J_MAX; j++) {
				matrix[i][j] -= _matrix.getValueAt(i, j);
			}
		}

		return (*this);
	}

	bool multiply(Matrix _matrix) {
		int **arr2d;
		arr2d = new int*[MATRIX_MAX_SIZE];
		for (int i = 0; i < MATRIX_MAX_SIZE; i++) {
			arr2d[i] = new int[MATRIX_MAX_SIZE];
			for (int j = 0; j < MATRIX_MAX_SIZE; j++) {
				arr2d[i][j] = 0;
			}
		}
		for (int i = 0; i < I_MAX; i++) {
			for (int count = 0; count < _matrix.getMaxJ(); count++) {
				int result = 0;
				for (int j = 0; j < J_MAX; j++) {
					result += matrix[i][j] * _matrix.getValueAt(j, count);
				}
				arr2d[i][count] = result;
			}
		}
		J_MAX = _matrix.getMaxJ();
		matrix = arr2d;
		return true;
	}

	bool multiply(Vector v) {

		int **arr2d;
		arr2d = new int*[MATRIX_MAX_SIZE];

		int _matrix[3] = { v.x, v.y, v.z };

		for (int i = 0; i < MATRIX_MAX_SIZE; i++) {
			arr2d[i] = new int[MATRIX_MAX_SIZE];
			for (int j = 0; j < MATRIX_MAX_SIZE; j++) {
				arr2d[i][j] = 0;
			}
		}

		for (int i = 0; i < I_MAX; i++) {
			for (int count = 0; count < 1; count++) { // 1 -> vector to matrices J or Column count
				int result = 0;
				for (int j = 0; j < J_MAX; j++) {
					result += matrix[i][j] * _matrix[j];
				}
				arr2d[i][count] = result;
			}
		}
		J_MAX = 1;
		matrix = arr2d;
		return true;
	}

	void Transpose() {
		int ** transpose_matrix = new int*[MATRIX_MAX_SIZE];
		for (int i = 0; i < MATRIX_MAX_SIZE; i++) {
			transpose_matrix[i] = new int[MATRIX_MAX_SIZE];
			for (int j = 0; j < MATRIX_MAX_SIZE; j++) {
				transpose_matrix[i][j] = matrix[j][i];
			}
		}
		int temp = I_MAX;
		I_MAX = J_MAX;
		J_MAX = temp;
		matrix = transpose_matrix;
	}

	void print() {
		for (int i = 0; i < I_MAX; i++) {
			for (int j = 0; j < J_MAX; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	bool plusMatrix(Matrix _matrix) {
		// CHECK MATRIX'S HEIGHT AND WEIGHT
		if (_matrix.getMaxI() != I_MAX || _matrix.getMaxJ() != J_MAX)
			return false;

		for (int i = 0; i < I_MAX; i++) {
			for (int j = 0; j < J_MAX; j++) {
				matrix[i][j] += _matrix.getValueAt(i, j);
			}
		}

		return true;
	}

	bool minusMatrix(Matrix _matrix) {
		// CHECK MATRIX'S HEIGHT AND WEIGHT
		if (_matrix.getMaxI() != I_MAX || _matrix.getMaxJ() != J_MAX)
			return false;

		for (int i = 0; i < I_MAX; i++) {
			for (int j = 0; j < J_MAX; j++) {
				matrix[i][j] -= _matrix.getValueAt(i, j);
			}
		}

		return true;
	}

	float getDeterminant() {
		float determinant = 0;
		for (int i = 0; i < 3; i++) {
			determinant += (matrix[0][i] * (matrix[1][(i + 1) % 3] * matrix[2][(i + 2) % 3] - matrix[1][(i + 2) % 3] * matrix[2][(i + 1) % 3]));
		}
		return determinant;
	}

	float **getInverse() {
		float ** temp = createArr2d();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				temp[i][j] = ((matrix[(j + 1) % 3][(i + 1) % 3] * matrix[(j + 2) % 3][(i + 2) % 3]) - (matrix[(j + 1) % 3][(i + 2) % 3] * matrix[(j + 2) % 3][(i + 1) % 3])) / getDeterminant();
				cout << temp[i][j] << " ";
			}
			cout << endl;
		}
		return temp;
	}

	float **createArr2d() {
		float **temp = new float*[MATRIX_MAX_SIZE];
		for (int i = 0; i < MATRIX_MAX_SIZE; i++) {
			temp[i] = new float[MATRIX_MAX_SIZE];
			for (int j = 0; j < MATRIX_MAX_SIZE; j++) {
				temp[i][j] = 0;
			}
		}
		return temp;
	}

	int getMaxI() {
		return I_MAX;
	}

	int getMaxJ() {
		return J_MAX;
	}

};