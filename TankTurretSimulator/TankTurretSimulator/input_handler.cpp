#include "input_handler.h"

float InputHandler::width;
float InputHandler::height;
float InputHandler::mouseX;
float InputHandler::mouseY;
std::unordered_map<int, bool> InputHandler::keyStates;
std::unordered_map<int, bool> InputHandler::toggledStates;
std::unordered_map<int, bool> InputHandler::mouseButtonStates;
std::unordered_map<int, bool> InputHandler::mouseButtonToggledStates;

void InputHandler::init(GLFWwindow* window, float w, float h) {
    width = w;
    height = h;
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && !keyStates[key]) {
        keyStates[key] = true;
        toggledStates[key] = !toggledStates[key];
    }
    else if (action == GLFW_RELEASE) {
        keyStates[key] = false;
    }
}

void InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS && !mouseButtonStates[button]) {
        mouseButtonStates[button] = true;
        mouseButtonToggledStates[button] = !mouseButtonToggledStates[button];

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            mouseX = (static_cast<float>(xpos) / width) * 2.0f - 1.0f;
            mouseY = 1.0f - (static_cast<float>(ypos) / height) * 2.0f;
        }
    }
    else if (action == GLFW_RELEASE) {
        mouseButtonStates[button] = false;
    }
}

bool InputHandler::isKeyPressed(int key) {
    return keyStates[key];
}

bool InputHandler::isKeyToggled(int key) {
    return toggledStates[key];
}

bool InputHandler::isMouseButtonPressed(int button) {
    return mouseButtonStates[button];
}

bool InputHandler::isMouseButtonToggled(int button) {
    return mouseButtonToggledStates[button];
}