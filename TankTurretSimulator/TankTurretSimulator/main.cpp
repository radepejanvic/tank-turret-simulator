#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "led.h"
#include "input_handler.h"
#include "voltmeter.h"
#include "ammo.h"
#include "turret.h"
#include "visor.h"
#include "panorama.h"

#include <GL/glew.h>   
#include <GLFW/glfw3.h>

#include <thread>
#include <chrono>

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

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Tank Turret Simulator", monitor, NULL);
    //GLFWwindow* window = glfwCreateWindow(1600, 900, "Tank Turret Simulator", NULL, NULL);
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
    Turret turret;
    Visor visor(-0.6, 0.7, 5.0);
    Panorama panorama(0.0, 0.0, 7.0, 2.0);


    glClearColor(0.8902, 0.8902, 0.8902, 1.0);
    while (!glfwWindowShouldClose(window)) 
    {
        if (InputHandler::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        turret.draw();
        turret.fire();
        //visor.draw();
        panorama.draw();

        if (InputHandler::isKeyPressed(GLFW_KEY_D)) {
            panorama.moveRight(0.001);
        }

        if (InputHandler::isKeyPressed(GLFW_KEY_A)) {
            panorama.moveLeft(0.001);
        }

        glfwSwapBuffers(window);
        glfwPollEvents(); 

    }

    glfwTerminate();
    return 0;
}
