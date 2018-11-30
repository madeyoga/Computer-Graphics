#pragma once

class Camera {
public:
	Matrix2 __matrix_transformation;	// c
	Vector __current_position;			// pos

	Camera() {
		__matrix_transformation = Matrix2();
		__current_position = Vector(0, 0, 0, 1);
	}

	void transform_matrix(Vector __v) {
		__matrix_transformation = __matrix_transformation.multiplies(__v);
	}

	Vector transform_camera(Vector __v) {
		Vector __result = __matrix_transformation.multiplies(__v);
		__result.z = __result.z * -1;
		return __result;
	}

	void change_view_x(float _value) {
		__matrix_transformation._matrix[0][3] += _value;
		// __current_position.x += _value * -1;
		// __current_position.x -= _value;
	}

	void change_view_y(float _value) {
		__matrix_transformation._matrix[1][3] += _value;
		// __current_position.y += _value * -1;
	}

	void change_view_z(float _value) {
		__matrix_transformation._matrix[2][3] += _value;
		// __current_position.z += _value * -1;
	}

	void rotate(Vector __v, float __degree) {
		float u = __v.x;
		float v = __v.y;
		float w = __v.z;

		float deg = 3.14 * __degree / 180;
		
		Matrix2 m;

		m._matrix[0][0] = pow(u, 2.0) + (pow(v, 2.0) + pow(w, 2.0)) * cos(deg);
		m._matrix[0][1] = u * v * (1 - cos(deg)) - w * sin(deg);
		m._matrix[0][2] = u * w * (1 - cos(deg)) + v * sin(deg);

		m._matrix[1][0] = u * v * (1 - cos(deg) + w * sin(deg));
		m._matrix[1][1] = v * v + (u * u + w * w) * cos(deg);
		m._matrix[1][2] = v * w * (1 - cos(deg)) - u * sin(deg);

		m._matrix[2][0] = u * w * (1 - cos(deg)) - v * sin(deg);
		m._matrix[2][1] = v * w * (1 - cos(deg)) + u * sin(deg);
		m._matrix[2][2] = w * w + (u * u + v * v) * cos(deg);
		/******************************************************************************/
		m._matrix[0][0] = pow(u, 2.0) + (pow(v, 2.0) + pow(w, 2.0)) * cos(deg);
		m._matrix[0][1] = u * v * (1 - cos(deg)) - w * sin(deg);
		m._matrix[0][2] = u * w * (1 - cos(deg)) + v * sin(deg);

		m._matrix[1][0] = u * v * (1 - cos(deg)) + w * sin(deg);
		m._matrix[1][1] = v * v + (u * u + w * w) * cos(deg);
		m._matrix[1][2] = v * w * (1 - cos(deg)) - u * sin(deg);

		m._matrix[2][0] = u * w * (1 - cos(deg)) - v * sin(deg);
		m._matrix[2][1] = v * w * (1 - cos(deg)) + u * sin(deg);
		m._matrix[2][2] = w * w + (u * u + v * v) * cos(deg);



		m._matrix[0][3] = (__current_position.x * (v * v + w * w) - u * (__current_position.y * v + __current_position.z * w)) 
			* (1 - cos(deg)) + (__current_position.y * w - __current_position.z * v) * sin(deg);
		m._matrix[1][3] = (__current_position.y * (u * u + w * w) - v * (__current_position.x * u + __current_position.z * w)) 
			* (1 - cos(deg)) + (__current_position.z * u - __current_position.x * w) * sin(deg);
		m._matrix[2][3] = (__current_position.z * (u * u + v * v) - w * (__current_position.x * u + __current_position.y * v))
			* (1 - cos(deg)) + (__current_position.x * v - __current_position.y * u) * sin(deg);

		__matrix_transformation = m.multiplies(__matrix_transformation);

	}

};
