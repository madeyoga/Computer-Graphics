#pragma once

class Transformation {

public:

	Matrix2 rotate_x(float _angle_theta) {
		Matrix2 __matrix_temp;
		__matrix_temp._matrix[1][1] = cos(_angle_theta);
		__matrix_temp._matrix[1][2] = -sin(_angle_theta);
		__matrix_temp._matrix[2][1] = sin(_angle_theta);
		__matrix_temp._matrix[2][2] = cos(_angle_theta);
		return __matrix_temp;
	}

	Matrix2 rotate_y(float _angle_theta) {
		Matrix2 __matrix_temp;
		__matrix_temp._matrix[0][0] = cos(_angle_theta);
		__matrix_temp._matrix[0][2] = sin(_angle_theta);
		__matrix_temp._matrix[2][0] = -sin(_angle_theta);
		__matrix_temp._matrix[2][2] = cos(_angle_theta);
		return __matrix_temp;
	}

	Matrix2 rotate_z(float _angle_theta) {
		Matrix2 __matrix_temp;
		__matrix_temp._matrix[0][0] = cos(_angle_theta);
		__matrix_temp._matrix[0][1] = -sin(_angle_theta);
		__matrix_temp._matrix[1][0] = sin(_angle_theta);
		__matrix_temp._matrix[1][1] = cos(_angle_theta);
		return __matrix_temp;
	}

	Matrix2 translate(Vector __vector) {
		Matrix2 __matrix_temp;
		__matrix_temp._matrix[0][3] = __vector.x;
		__matrix_temp._matrix[1][3] = __vector.y;
		__matrix_temp._matrix[2][3] = __vector.z;
		__matrix_temp._matrix[3][3] = 1;
		return __matrix_temp;
	}

	Matrix2 translate(Matrix2 __matrix_temp, Vector __vector) {
		__matrix_temp._matrix[0][3] = __vector.x;
		__matrix_temp._matrix[1][3] = __vector.y;
		__matrix_temp._matrix[2][3] = __vector.z;
		__matrix_temp._matrix[3][3] = 1;
		return __matrix_temp;
	}

	Matrix2 scale(Vector __vector) {
		Matrix2 __matrix_temp;
		__matrix_temp._matrix[0][0] = __vector.x;
		__matrix_temp._matrix[1][1] = __vector.y;
		__matrix_temp._matrix[2][2] = __vector.z;
		return __matrix_temp;
	}

};