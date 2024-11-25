#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "input_handler.h"

int main() {
	if (!glfwInit()) {
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1000, 560, "Hello, window!", NULL, NULL);
	//GLFWwindow* window = glfwCreateWindow(1600, 900, "Hello, window!", glfwGetPrimaryMonitor(), NULL);

	if (window == NULL) {
		glfwTerminate();
		return 2; 
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return 3; 
	}

	glClearColor(0.25, 0.0, 0.25, 1);

	InputHandler::init(window);

	while (!glfwWindowShouldClose(window)) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		if (InputHandler::isKeyToggled(GLFW_KEY_A)) {
			std::cout << "Da" << std::endl;
		}
		else {
			std::cout << "Ne" << std::endl;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}