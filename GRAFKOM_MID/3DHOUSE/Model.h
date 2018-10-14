#pragma once

#include <iostream>
#include <vector>
#include "Vector.h"
#include "Matrix2.h"
using namespace std;

class Model {
public:
	 vector <Vector> __vertrices;
	 Matrix2 transformation_matrix;

	 void add_point(Vector __v) {
		 __vertrices.push_back(__v);
	 }

	 void draw_cylinder(int __rad, int __height, int __size) {
		 for (int i = -(__height / 2); i < __height / 2; i += __size) {
			 int __count = 0;
			 for (float j = -3.14; j < 3.14; j += 0.01) {
				 float __x1 = __rad * sin(j);
				 float __y1 = __rad * cos(j);
				 glBegin(GL_POINTS);

				 glVertex3d(__x1, i, __y1);

				 glEnd();
				 if (i + __size < (__height / 2)) {
					 __count++;
					 if (__count%__size == 0) {
						 glBegin(GL_LINES);

						 glVertex3d(__x1, i + __size, __y1);
						 glVertex3d(__x1, i, __y1);

						 glEnd();
					 }
				 }

			 }
		 }
	 }

	 void draw_wire_frame(int row, int col, int size){
		 glBegin(GL_LINES);
		 for (int i = -(row / 2); i < row / 2; i += size) {
			 for (int j = -(col / 2); j < col / 2; j += size) {
				 glVertex3d(j, i, 0);
				 glVertex3d(j + size, i, 0);

				 glVertex3d(j, i, 0);
				 glVertex3d(j, i + size, 0);
			 }
		 }
		 glEnd();
	 }

	 void draw_polygon() {
		 glBegin(GL_POLYGON);

		 for (int i = 0; i < __vertrices.size(); i++) {
			 Vector __vertex = transformation_matrix.multiplies(__vertrices[i]);
			 float x = __vertex.x;
			 float y = __vertex.y;
			 float z = __vertex.z;
			 glVertex3f(x, y, z);
		 }

		 glEnd();
	 }

	 void draw_lines() {
		 glBegin(GL_LINES);

		 for (int i = 0; i < __vertrices.size(); i++) {
			 Vector __vertex = transformation_matrix.multiplies(__vertrices[i]);
			 float x = __vertex.x;
			 float y = __vertex.y;
			 float z = __vertex.z;
			 glVertex3f(x, y, z);
		 }

		 glEnd();
	 }

	 void draw_triangles() {
		 glBegin(GL_TRIANGLES);

		 for (int i = 0; i < __vertrices.size(); i++) {
			 Vector __vertex = transformation_matrix.multiplies(__vertrices[i]);
			 float x = __vertex.x;
			 float y = __vertex.y;
			 float z = __vertex.z;
			 glVertex3f(x, y, z);
		 }

		 glEnd();
	 }

	 void draw_quads() {
		 glBegin(GL_QUADS);

		 for (int i = 0; i < __vertrices.size(); i++) {
			 Vector __vertex = transformation_matrix.multiplies(__vertrices[i]);
			 float x = __vertex.x;
			 float y = __vertex.y;
			 float z = __vertex.z;
			 glVertex3f(x, y, z);
		 }

		 glEnd();
	 }

};