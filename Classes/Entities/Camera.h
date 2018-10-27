#pragma once

class Camera {
public:
	Matrix2 __matrix_transformation;	// c
	Vector __current_position;			// pos

	Camera() {
		__matrix_transformation = Matrix2();
		__current_position = Vector(0, 0, 0, 1);
	}

	Vector transform_camera(Vector __v) {
		Vector __result = __matrix_transformation.multiplies(__v);
		__result.z = __result.z * -1;
		return __result;
	}

	void change_view_x(float _value) {
		__matrix_transformation._matrix[0][3] += _value;
		__current_position.x += _value * -1;
	}

	void change_view_y(float _value) {
		__matrix_transformation._matrix[1][3] += _value;
		__current_position.y += _value * -1;
	}

	void change_view_z(float _value) {
		__matrix_transformation._matrix[2][3] += _value;
		__current_position.z += _value * -1;
	}

};
