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

	// new
	std::vector<Vector> vertexes, nvektor;
	std::vector<Vector> vn;
	std::vector<Vector> vt;

	Matrix2 matrix_transform;

	Material material;
	Lightning light;

	Mesh() {
		matrix_transform = Transformation().translate(Vector(20, 20, 20, 1));
		material.set_color(RGBColor(0, 1, 0.75));
		light.set_light(100, 100, -100);
	}

	bool loadObject_poly(std::string file_path) {

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

		//for (int i = 0; i < uv_indices.size(); i++) {
		//	int uv_index = uv_indices[i];
		//	Vector uv = uvs[uv_index - 1];
		//	out_uvs.push_back(uv);
		//}

		//for (int i = 0; i < normals.size(); i++) {
		//	int normal_index = normal_indices[i];
		//	Vector normal = normals[normal_index - 1];
		//	out_normals.push_back(normal);
		//}
		
		return true;
	}

	bool loadObject_square(std::string file_path) {

		FILE *file = fopen(file_path.c_str()/*converts to const char* */, "r");
		//ifstream infile(file_path);
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
			//string line;
			//getline(infile, line);
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
			else if (strcmp(lineHeader, "f") == 0) 
			{
				int vertexIndex[4], uvIndex[4], normalIndex[4];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
				if (matches < 12)
				{
					vertex_indices.push_back(vertexIndex[0]);
					vertex_indices.push_back(vertexIndex[1]);
					vertex_indices.push_back(vertexIndex[2]);
					vertex_indices.push_back(vertexIndex[3]);
					uv_indices.push_back(uvIndex[0]);
					uv_indices.push_back(uvIndex[1]);
					uv_indices.push_back(uvIndex[2]);
					uv_indices.push_back(uvIndex[3]);
					normal_indices.push_back(normalIndex[0]);
					normal_indices.push_back(normalIndex[1]);
					normal_indices.push_back(normalIndex[2]);
					normal_indices.push_back(normalIndex[3]);

					Face face;
					face.vertex_indices.push_back(vertexIndex[0]);
					face.vertex_indices.push_back(vertexIndex[1]);
					face.vertex_indices.push_back(vertexIndex[2]);
					face.vertex_indices.push_back(vertexIndex[3]);
					face.uv_indices.push_back(uvIndex[0]);
					face.uv_indices.push_back(uvIndex[1]);
					face.uv_indices.push_back(uvIndex[2]);
					face.uv_indices.push_back(uvIndex[3]);
					face.normal_indices.push_back(normalIndex[0]);
					face.normal_indices.push_back(normalIndex[1]);
					face.normal_indices.push_back(normalIndex[2]);
					face.normal_indices.push_back(normalIndex[3]);
					faces.push_back(face);
					fscanf(file, "\n");
					continue;
				}
				// OLD METHODS
				//cout << matches << endl;
				vertex_indices.push_back(vertexIndex[0]);
				vertex_indices.push_back(vertexIndex[1]);
				vertex_indices.push_back(vertexIndex[2]);
				vertex_indices.push_back(vertexIndex[3]);
				uv_indices.push_back(uvIndex[0]);
				uv_indices.push_back(uvIndex[1]);
				uv_indices.push_back(uvIndex[2]);
				uv_indices.push_back(uvIndex[3]);
				normal_indices.push_back(normalIndex[0]);
				normal_indices.push_back(normalIndex[1]);
				normal_indices.push_back(normalIndex[2]);
				normal_indices.push_back(normalIndex[3]);

				Face face;
				face.vertex_indices.push_back(vertexIndex[0]);
				face.vertex_indices.push_back(vertexIndex[1]);
				face.vertex_indices.push_back(vertexIndex[2]);
				face.vertex_indices.push_back(vertexIndex[3]);
				face.uv_indices.push_back(uvIndex[0]);
				face.uv_indices.push_back(uvIndex[1]);
				face.uv_indices.push_back(uvIndex[2]);
				face.uv_indices.push_back(uvIndex[3]);
				face.normal_indices.push_back(normalIndex[0]);
				face.normal_indices.push_back(normalIndex[1]);
				face.normal_indices.push_back(normalIndex[2]);
				face.normal_indices.push_back(normalIndex[3]);
				faces.push_back(face);

			}
		}

		// OLD METHODS 
		for (int i = 0; i < vertex_indices.size(); i++) {
			int vertex_index = vertex_indices[i];
			Vector vertex = vertices[vertex_index - 1];
			out_vertices.push_back(vertex);
		}

		//for (int i = 0; i < uv_indices.size(); i++) {
		//	int uv_index = uv_indices[i];
		//	Vector uv = uvs[uv_index - 1];
		//	out_uvs.push_back(uv);
		//}

		//for (int i = 0; i < normals.size(); i++) {
		//	int normal_index = normal_indices[i];
		//	Vector normal = normals[normal_index - 1];
		//	out_normals.push_back(normal);
		//}

		return true;
	}

	bool loadObject_(const char *filename)
	{
		FILE *file;
		char *s;
		s = new char[2];
		float v1, v2, v3;
		file = fopen(filename, "r");
		if (file == NULL) 
		{
			std::cout << "Unable to open file " << filename << std::endl;
			return false;
		}
		try {
			while (!feof(file))
			{
				fscanf(file, "%s", s);
				if (strcmp(s, "v") == 0)
				{
					fscanf(file, "%f %f %f", &v1, &v2, &v3);
					Vector v(v1 * 25, v2 * 25, v3 * 25, 1);
					vertexes.push_back(v);
					nvektor.push_back(v);

				}
				else if (strcmp(s, "f") == 0)
				{
					int count = 0;
					int arr[100], arr2[100], arr3[100];
					int cek;
					do {
						fscanf(file, "%d/%d/%d", &arr[count], &arr2[count], &arr3[count]);

						arr[count]--;
						arr2[count]--;
						arr3[count]--;
						cek = fgetc(file);
						count++;
					} while (cek != 10 && cek != -1);
					Face face(count);
					face.LoadFace(arr, arr2, arr3);
					faces.push_back(face);

				}
				else if (strcmp(s, "vn") == 0)
				{
					fscanf(file, "%f %f %f", &v1, &v2, &v3);
					Vector v(v1, v2, v3, 1);
					vn.push_back(v);

				}
				else if (strcmp(s, "vt") == 0)
				{
					fscanf(file, "%f %f %f", &v1, &v2, &v3);
					Vector v(v1, v2, v3, 1);
					vt.push_back(v);

				}
				else if (strcmp(s, "s") == 0)
				{
					int s_;
					fscanf(file, "%d", &s_);

				}
			}
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
		delete s;
		fclose(file);
		
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

	void drawMesh(Camera cam) 
	{
		Matrix2 m = cam.__matrix_transformation.multiplies(matrix_transform);
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
			glBegin(GL_POLYGON);
			for (int j = 0; j < faces[i].vertex_indices.size(); j++) {
				v[j] = m.multiplies(vertices[faces[i].vertex_indices[j] - 1]);
				glVertex3f(v[j].x, v[j].y, v[j].z);
				// out_vertices[faces[i].vertex_indices[j]] = v[j];
			}
			glEnd();
			delete [] v;

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

	void drawMesh_(Camera cam)
	{
		for (int i = 0; i < faces.size(); i++)
		{
			glPointSize(1);
			RGBColor temp;
			temp = material.get_ambient()
			.plus(
				material.get_diffuse(
					nvektor[faces[i].v[0]], 
					nvektor[faces[i].v[1]], 
					nvektor[faces[i].v[2]], 
					light
				)
			).plus(
				material.get_specular(
					nvektor[faces[i].v[0]], 
					nvektor[faces[i].v[1]], 
					nvektor[faces[i].v[2]],
					light, 
					cam.__current_position
				)
			);
			glColor3f(temp.r, temp.g, temp.b);

			Vector *v;
			v = new Vector[faces[i].length];
			for (int j = 0; j < faces[i].length; j++)
			{
				v[j] = vertexes[faces[i].v[j]];
				nvektor[faces[i].v[j]] = cam.__matrix_transformation.multiplies(matrix_transform.multiplies(v[j]));
			}
			delete [] v;

			glBegin(GL_POLYGON);

			for (int j = 0; j < faces[i].length; j++)
			{
				glVertex3f(nvektor[faces[i].v[j]].x, nvektor[faces[i].v[j]].y, nvektor[faces[i].v[j]].z);
			}
			glDisable(GL_TEXTURE_2D);

			glEnd();
		}
	}

};