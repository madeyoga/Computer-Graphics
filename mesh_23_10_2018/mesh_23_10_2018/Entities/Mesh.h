#pragma once

class Mesh {
public:
	std::vector <Face> faces;

	// TEMP
	std::vector <Vector> vertices;  // v
	std::vector <Vector> uvs;      //  vt
	std::vector <Vector> normals; //   vn

	// OUTPUT 
	std::vector <Vector> out_vertices;  // v
	std::vector <Vector> out_uvs;      //  vt
	std::vector <Vector> out_normals; //   vn

	// FACES
	std::vector <int> vertex_indices;
	std::vector <int> uv_indices;
	std::vector <int> normal_indices;

	Matrix2 matrix_transform;

	Material material;
	Lightning light;

	Mesh() {
		matrix_transform = Transformation().translate(Vector(0, 0, 50, 1));
		material.set_color(RGBColor(1, 1, 0));
		light.set_light(-50, 50, 0);
	}

	bool loadObject(std::string file_path) {

		FILE *file = fopen(file_path.c_str()/*converts to const char* */, "r");
		if (file == NULL) {
			std::cout << "Unable to open file " << file_path << std::endl;
			return false;
		}
		int line = 1;
		while (true) {
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
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
				if (matches < 9) {
					std::cout << "parser cannot read file, invalid syntax!" << std::endl;
					return false;
				}


				// OLD METHODS
				vertex_indices.push_back(vertexIndex[0]);
				vertex_indices.push_back(vertexIndex[1]);
				vertex_indices.push_back(vertexIndex[2]);
				uv_indices.push_back(uvIndex[0]);
				uv_indices.push_back(uvIndex[1]);
				uv_indices.push_back(uvIndex[2]);
				normal_indices.push_back(normalIndex[0]);
				normal_indices.push_back(normalIndex[1]);
				normal_indices.push_back(normalIndex[2]);

				Face face;
				face.vertex_indices.push_back(vertexIndex[0]);
				face.vertex_indices.push_back(vertexIndex[1]);
				face.vertex_indices.push_back(vertexIndex[2]);
				face.uv_indices.push_back(uvIndex[0]);
				face.uv_indices.push_back(uvIndex[1]);
				face.uv_indices.push_back(uvIndex[2]);
				face.normal_indices.push_back(normalIndex[0]);
				face.normal_indices.push_back(normalIndex[1]);
				face.normal_indices.push_back(normalIndex[2]);
				faces.push_back(face);

			}
		}

		// OLD METHODS 
		for (int i = 0; i < vertex_indices.size(); i++) {
			int vertex_index = vertex_indices[i];
			Vector vertex = vertices[vertex_index - 1];
			out_vertices.push_back(vertex);
		}

		for (int i = 0; i < uv_indices.size(); i++) {
			int uv_index = uv_indices[i];
			Vector uv = uvs[uv_index - 1];
			out_uvs.push_back(uv);
		}

		for (int i = 0; i < normals.size(); i++) {
			int normal_index = normal_indices[i];
			Vector normal = normals[normal_index - 1];
			out_normals.push_back(normal);
		}
		
		return true;
	}

	void drawMesh() {
		for (int i = 0; i < faces.size(); i++) {
			Vector *v;
			v = new Vector[faces[i].vertex_indices.size()];
			for (int j = 0; j < faces[i].vertex_indices.size(); j++) {
				v[j] = matrix_transform.multiplies(vertices[faces[i].vertex_indices[j] - 1]);
				out_vertices[faces[i].vertex_indices[j]] = v[j];
			}
			// delete v; error;

			glBegin(GL_POLYGON);
			for (int j = 0; j < faces[i].vertex_indices.size(); j++) {
				glVertex3f(out_vertices[faces[i].vertex_indices[j]].x, out_vertices[faces[i].vertex_indices[j]].y, out_vertices[faces[i].vertex_indices[j]].z);
			}
			glEnd();
		}

		// OLD METHODS
		//glBegin(GL_LINES);
		//for (int i = 0; i < out_vertices.size(); i++) {
		//	Vector v = matrix_transform.multiplies(out_vertices[i]);
		//	// glVertex3f(out_vertices[i].x, out_vertices[i].y, out_vertices[i].z);
		//	glVertex3f(v.x, v.y, v.z);
		//}
		//glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void drawMesh(Camera cam) {

		for (int i = 0; i < faces.size(); i++) {

			RGBColor temp = material.get_ambient()
				.plus(
					material.get_diffuse(
						vertices[faces[i].vertex_indices[0] - 1],
						vertices[faces[i].vertex_indices[1] - 1],
						vertices[faces[i].vertex_indices[2] - 1],
						light
					)
					.plus(
						material.get_specular(
							vertices[faces[i].vertex_indices[0] - 1],
							vertices[faces[i].vertex_indices[1] - 1],
							vertices[faces[i].vertex_indices[2] - 1],
							light,
							cam.__current_position
						)
					)
				);
			glColor3f(temp.r, temp.g, temp.b);

			Vector *v;
			v = new Vector[faces[i].vertex_indices.size()];
			for (int j = 0; j < faces[i].vertex_indices.size(); j++) {
				// v[j] = cam.__matrix_transformation.multiplies(vertices[faces[i].vertex_indices[j] - 1]);

				// scaled object 
				v[j] = cam.__matrix_transformation.multiplies(matrix_transform).multiplies(vertices[faces[i].vertex_indices[j] - 1]);

				out_vertices[faces[i].vertex_indices[j]] = v[j];
			}
			// delete v; error;

			glBegin(GL_POLYGON);
			for (int j = 0; j < faces[i].vertex_indices.size(); j++) {
				glVertex3f(out_vertices[faces[i].vertex_indices[j]].x, out_vertices[faces[i].vertex_indices[j]].y, out_vertices[faces[i].vertex_indices[j]].z);
			}
			glEnd();
		}

		// OLD METHODS
		//glBegin(GL_LINES);
		//for (int i = 0; i < out_vertices.size(); i++) {
		//	Vector v = matrix_transform.multiplies(out_vertices[i]);
		//	// glVertex3f(out_vertices[i].x, out_vertices[i].y, out_vertices[i].z);
		//	glVertex3f(v.x, v.y, v.z);
		//}
		//glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	void print_vertrices() {
		for (int i = 0; i < out_vertices.size(); i++) {
			std::cout << out_vertices[i].x << " "
				<< out_vertices[i].y << " "
				<< out_vertices[i].z << std::endl;
		}
	}

};