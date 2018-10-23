#pragma once

class Face {
public:
	vector<int> vertex_indices, normal_indices, uv_indices;
	Face() {

	}
	Face(vector<int> &v1, vector<int> &v2, vector<int> &v3) {
		vertex_indices = v1;
		normal_indices = v2;
		uv_indices = v3;
	}
};