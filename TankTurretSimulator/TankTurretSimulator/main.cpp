#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include "shader.h"
#include "led.h"
#include "input_handler.h"
#include "voltmeter.h"
#include "ammo.h"

#include <GL/glew.h>   
#include <GLFW/glfw3.h>

#include <thread>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void handleFire(Ammo& ammo, LED& led) {
    // Fire a shot
    ammo.fire();

    // Toggle the LED on
    led.toggle();

    // Start a separate thread for the timer
    std::thread timerThread([&led]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(7500)); // 7.5 seconds
        led.toggle(); // Toggle LED off
        });

    timerThread.detach(); // Detach so it doesn't block the main thread
}

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

    /*GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Tank Turret Simulator", monitor, NULL);*/
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
    Ammo ammo(10, 0.6, -0.5, 0.2, 1.0, 0.02);
    LED led(0.5, -0.45, 0.1);
    Voltmeter voltmeter(20, 1, -0.6, -0.3, 0.5);
    //voltmeter.increase();
    //voltmeter.increase();
    //voltmeter.increase();

    int i = 0;

    glClearColor(0.8902, 0.8902, 0.8902, 1.0);
    while (!glfwWindowShouldClose(window)) 
    {
        if (InputHandler::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        led.draw();
        voltmeter.draw();
        ammo.draw();

        glfwSwapBuffers(window);
        glfwPollEvents(); 

        if (i == 0) {
            handleFire(ammo, led);
            i++;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        voltmeter.increase();
        //ammo.fire();
        //led.toggle();

    }

    glfwTerminate();
    return 0;
}
