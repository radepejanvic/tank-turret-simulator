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
#include "target.h"
#include "text_handler.h"

#include <GL/glew.h>   
#include <GLFW/glfw3.h>

#include <thread>
#include <chrono>
#include <map>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



const int TARGET_FPS = 60;
const int FRAME_DURATION_MS = 1000 / TARGET_FPS;

auto lastFrameTime = std::chrono::high_resolution_clock::now();

void limitFPS() {
    auto currentFrameTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFrameTime - lastFrameTime).count();

    if (elapsedTime < FRAME_DURATION_MS) {
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DURATION_MS - elapsedTime));
    }
    lastFrameTime = std::chrono::high_resolution_clock::now();
}

std::chrono::steady_clock::time_point startTime;
bool missionOver = false;
std::string missionStatus = "";


int main(void)
{
    if (!glfwInit()) 
    {
        std::cout << "GLFW::NOT_LOADED" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    //GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Tank Turret Simulator", monitor, NULL);
    GLFWwindow* window = glfwCreateWindow(1600, 900, "Tank Turret Simulator", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "WINDOW::NOT_CREATED" << std::endl;
        glfwTerminate(); 
        return 2;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
        std::cout << "GLEW::NOT_INITIALIZED" << std::endl;
        return 3;
    }

    InputHandler::init(window, 1600, 900);
    TextHandler text("C:/Windows/Fonts/arial.ttf");
    
    Turret turret(0.01);

    bool isEnterier = true; 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.8902, 0.8902, 0.8902, 1.0);
    while (!glfwWindowShouldClose(window)) 
    {
        if (InputHandler::isKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        if (InputHandler::isKeyPressed(GLFW_KEY_D)) {
            turret.moveRight();
        }

        if (InputHandler::isKeyPressed(GLFW_KEY_A)) {
            turret.moveLeft();
        }

        if (InputHandler::isKeyPressed(GLFW_KEY_V)) {
            isEnterier = false;
        }

        if (InputHandler::isKeyPressed(GLFW_KEY_C)) {
            isEnterier = true;
        }

        if (InputHandler::isKeyPressed(GLFW_KEY_S)) {
            turret.decreaseV();
        }

        if (InputHandler::isKeyPressed(GLFW_KEY_W)) {
            turret.increaseV();
        }

        if (InputHandler::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
            turret.fire(InputHandler::mouseX, InputHandler::mouseY);
        }


        turret.draw(isEnterier); 
        
        text.renderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        text.renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

        glfwSwapBuffers(window);
        glfwPollEvents(); 
        limitFPS();

    }

    glfwTerminate();
    return 0;
}
