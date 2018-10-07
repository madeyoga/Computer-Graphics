//
//#include <GL\glew.h>
//#include <GLFW\glfw3.h>
#include "GL Libraries\GLUT\glut.h"
#include "Mesh.h"

#define WINDOW_SIZE 800

Mesh mesh;

void idle() {
	glutPostRedisplay();
}

void initCanvas() {
	// INIT CANVAS
	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

	// CLEAR
	glClearColor(0, 0, 0, 0);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_LINES);
	for (int i = 0; i < mesh.out_vertices.size(); i++) {
		glVertex3f(mesh.out_vertices[i].x, mesh.out_vertices[i].y, mesh.out_vertices[i].z);
	}
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char **argv) {

	
	mesh.loadObject("teko.txt");
	
	// INIT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("Bezier & Rumah");

	glutIdleFunc(idle);
	glutDisplayFunc(render);
	initCanvas();

	glutMainLoop();

	//float points[] = {
	//	100,  100,  10,
	//	500, 300,  50,
	//	700, -300,  50
	//};

	//glewExperimental = true; // Needed for core profile
	//if (!glfwInit())
	//{
	//	fprintf(stderr, "Failed to initialize GLFW\n");
	//	return -1;
	//}

	//// glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	//// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//															   // uncomment these lines if on Apple OS X
	//															   /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//															   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//															   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//															   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//															   // Open a window and create its OpenGL context
	//GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	//window = glfwCreateWindow(1366, 768, "Tutorial 01", NULL, NULL);
	//if (window == NULL) {
	//	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
	//	glfwTerminate();
	//	return -1;
	//}
	//glfwMakeContextCurrent(window); // Initialize GLEW
	//glewExperimental = true; // Needed in core profile
	//if (glewInit() != GLEW_OK) {
	//	fprintf(stderr, "Failed to initialize GLEW\n");
	//	return -1;
	//}

	//// This will identify our vertex buffer
	//GLuint vertexbuffer;
	//// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//glGenBuffers(1, &vertexbuffer);
	//// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//// Give our vertices to OpenGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points) * sizeof(GLfloat), points, GL_STATIC_DRAW);

	////GLuint vertexbuffer;
	////// Generate 1 buffer, put the resulting identifier in vertexbuffer
	////glGenBuffers(1, &vertexbuffer);
	////// The following commands will talk about our 'vertexbuffer' buffer
	////glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); 
	//
	//// Give our vertices to OpenGL.
	///*glBufferData(GL_ARRAY_BUFFER, mesh.out_vertices.size() * sizeof(Vector), &mesh.out_vertices[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, mesh.out_uvs.size() * sizeof(Vector), &mesh.out_uvs[0], GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, mesh.out_normals.size() * sizeof(Vector), &mesh.out_normals[0], GL_STATIC_DRAW);*/

	//// Ensure we can capture the escape key being pressed below

	//while (!glfwWindowShouldClose(window)) {
	//	// wipe the drawing surface clear
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	// glUseProgram(shader_programme);
	//	glBindVertexArray(vertexbuffer);
	//	// draw points 0-3 from the currently bound VAO with current in-use shader
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	// update other events like input handling 
	//	glfwPollEvents();
	//	// put the stuff we've been drawing onto the display
	//	glfwSwapBuffers(window);
	//}

	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//do {
	//	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	// 1st attribute buffer : vertices
	//	glEnableVertexAttribArray(0);
	//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//	glVertexAttribPointer(
	//		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//		3,                  // size
	//		GL_FLOAT,           // type
	//		GL_FALSE,           // normalized?
	//		0,                  // stride
	//		(void*)0            // array buffer offset
	//	);
	//	// Draw the triangle !
	//	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//	glDisableVertexAttribArray(0);

	//	// Swap buffers
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//	

	//} // Check if the ESC key was pressed or the window was closed
	//while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
	//	glfwWindowShouldClose(window) == 0);

	return 0;
}