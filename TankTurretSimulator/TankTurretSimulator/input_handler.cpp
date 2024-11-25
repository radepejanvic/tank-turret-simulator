#include "input_handler.h"

std::unordered_map<int, bool> InputHandler::keyStates;
std::unordered_map<int, bool> InputHandler::toggledStates;

void InputHandler::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyStates[key] = true;
        toggledStates[key] = !toggledStates[key];
    }
    else if (action == GLFW_RELEASE) {
        keyStates[key] = false;
    }
}

bool InputHandler::isKeyPressed(int key) {
    return keyStates[key];
}

bool InputHandler::isKeyToggled(int key) {
    return toggledStates[key];
}
