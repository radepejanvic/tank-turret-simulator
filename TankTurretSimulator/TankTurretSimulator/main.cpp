#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "led.h"
#include "input_handler.h"
#include "voltmeter.h"

#include <GL/glew.h>   
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void)
{
    if (!glfwInit()) 
    {
        std::cout << "GLFW::NOT LOADED" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Tank Turret Simulator", NULL, NULL); 
    if (window == NULL) 
    {
        std::cout << "WINDOW::NOT CREATED" << std::endl;
        glfwTerminate(); 
        return 2;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
        std::cout << "GLEW::NOT INITIALIZED" << std::endl;
        return 3;
    }

    InputHandler::init(window);
    LED led(0.2f, 0.2f, 0.2, 40);
    Voltmeter voltmeter(10, 1, -0.2, -0.2, 0.5, 0.5);

    while (!glfwWindowShouldClose(window)) 
    {
        if (InputHandler::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
     
        glClear(GL_COLOR_BUFFER_BIT);

        led.draw();
        voltmeter.draw();

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glfwTerminate();
    return 0;
}
