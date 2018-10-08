#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Face.h"
using namespace std;
class Mesh {
public:
	std::vector <Face> faces;
	std::vector <Vector> out_vertices; // v
	std::vector <Vector> out_uvs;      //  vt
	std::vector <Vector> out_normals; //   vn

	bool loadObject(std::string file_path) {
		std::vector <Vector> vertices; // v
		std::vector <Vector> uvs;      //  vt
		std::vector <Vector> normals; //   vn

		std::vector <int> vertex_indices;
		std::vector <int> uv_indices;
		std::vector <int> normal_indices;

		FILE *file = fopen(file_path.c_str()/*converts to const char* */, "r");
		if (file == NULL) {
			std::cout << "Unable to open file " << file_path << std::endl;
			return false;
		}
		int line = 1;
		while (true) {
			char lineHeader[128];
			int res = fscanf(file, "%s",lineHeader);
			if (res == EOF) {
				break;
			}
			if (strcmp(lineHeader, "v") == 0) {
				Vector vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				Vector uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				Vector normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					std::cout << "parser cannot read file, invalid syntax!" << std::endl;
					return false;
				}
				vertex_indices.push_back(vertexIndex[0]);
				vertex_indices.push_back(vertexIndex[1]);
				vertex_indices.push_back(vertexIndex[2]);
				uv_indices.push_back(uvIndex[0]);
				uv_indices.push_back(uvIndex[1]);
				uv_indices.push_back(uvIndex[2]);
				normal_indices.push_back(normalIndex[0]);
				normal_indices.push_back(normalIndex[1]);
				normal_indices.push_back(normalIndex[2]);

				// faces.push_back(Face(v1, v2, v3));
			}
		}
		for (int i = 0; i < vertex_indices.size(); i++) {
			int vertex_index = vertex_indices[i];
			Vector vertex = vertices[vertex_index - 1];
			out_vertices.push_back(vertex);

			int uv_index = uv_indices[i];
			Vector uv = uvs[uv_index - 1];
			out_uvs.push_back(uv);
			
			int normal_index = normal_indices[i];
			Vector normal = normals[normal_index - 1];
			out_normals.push_back(normal);
		}
		
		return true;
	}

	void print_vertrices() {
		for (int i = 0; i < out_vertices.size(); i++) {
			std::cout << out_vertices[i].x << " "
				<< out_vertices[i].y << " "
				<< out_vertices[i].z << std::endl;
		}
	}

};