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

	Matrix(int _i, int _j) { // default value
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

	Matrix(int _i, int _j, int **arr2d) {
		I_MAX = _i;
		J_MAX = _j;

		// CREATING ARRAY2D
		matrix = 0;
		matrix = new int*[MATRIX_MAX_SIZE];
		for (int i = 0; i < MATRIX_MAX_SIZE; i++) {
			matrix[i] = new int[MATRIX_MAX_SIZE];
			for (int j = 0; j < MATRIX_MAX_SIZE; j++) {
				matrix[i][j] = arr2d[i][j];
			}
		}
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
	
	// SKALAR
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

	Matrix operator*(Matrix _matrix) {
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
		// J_MAX = _matrix.getMaxJ();
		// matrix = arr2d;
		return (Matrix(I_MAX, _matrix.getMaxJ, arr2d));
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

Matrix operator*(int val, Matrix matrix) {
	for (int i = 0; i < matrix.getMaxI(); i++) {
		for (int j = 0; j < matrix.getMaxJ(); j++) {
			matrix.setValueAt(i, j, matrix.getValueAt(i, j) * val);
		}
	}
	return matrix;
}

void printMatrix(Matrix MATRIX) {
	for (int i = 0; i < MATRIX.getMaxI(); i++) {
		for (int j = 0; j < MATRIX.getMaxJ(); j++) {
			cout << MATRIX.getValueAt(i, j) << " ";
		}
		cout << endl;
	}
}

bool canMultiply(Matrix m1, Matrix m2) {
	if (m1.getMaxJ() == m2.getMaxI()) {
		return true;
	}
	return false;
}

float DotProductVector(const Vector &a, const Vector &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

Vector CrossProductVector(const Vector &a, const Vector &b) {
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	return Vector(x, y, z, 1);
}

void main() { 
	Matrix matrix1(3, 3), matrix2(3, 3);
	cout << "MATRIX 1: " << endl;
	printMatrix(matrix1);
	cout << "MATRIX 2: " << endl;
	printMatrix(matrix2);

	if (matrix1.plusMatrix(matrix2)) {
		cout << "jumlah 2 matrix: " << endl;
		printMatrix(matrix1);
	}
	else {
		cout << "ukuran Matrix tidak sama! tidak dapat dijumlahkan/dikurangkan!" << endl;
	}

	if (canMultiply(matrix1, matrix2)) {
		cout << "multiplies 2 matrix: " << endl;
		matrix2.multiply(matrix1);
		printMatrix(matrix2);
	}
	else
		cout << "Matrix tidak dapat dikalikan!" << endl;
	
	cout << "MATRIX * 2: " << endl;
	matrix2 = matrix2 * 2;
	printMatrix(matrix2);

	cout << "TRANSPOSE: " << endl;
	matrix2.Transpose();
	printMatrix(matrix2);

	cout << "OPERATOR - : " << endl;
	Matrix matrix3(3, 3);
	matrix2 = matrix2 - matrix3;
	printMatrix(matrix2);

	Matrix matrix4(3, 3);
	cout << "determinant matrix4: " << matrix4.getDeterminant() << endl;

	cout << "INVERSE MATRIX: " << endl;
	matrix4.getInverse();

	Vector v1(1, 3, 2, 1), v2(2, 3, 1, 1);

	cout << "DotProduct Vector: " << DotProductVector(v1, v2) << endl;
	Vector temp = CrossProductVector(v1, v2);
	cout << "CrossProduct Vector: " << temp.x << "i + " << temp.y << "j + " << temp.z << "k" << endl;

	Vector v3(1, 3, 2, 1);
	matrix1.multiply(v3);
	cout << "MATRIX1 MULTIPLY VECTOR : " << endl;
	printMatrix(matrix1);



	/*printMatrix(matrix1);
	printMatrix(matrix2);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << matrix1.getValueAt(i, j) << " ";
		}
		cout << endl;
	}*/
}
