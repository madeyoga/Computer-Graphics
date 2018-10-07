#pragma once
#include "Vector.h"

class Face {
public:
	Vector vertex_indices, normal_indices, uv_indices;
	Face(Vector &v1, Vector &v2, Vector &v3) {
		vertex_indices = v1;
		normal_indices = v2;
		uv_indices = v3;
	}
};