#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputHandler {
public:
    static float width, height, mouseX, mouseY;
    static void init(GLFWwindow* window, float w, float h);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static bool isKeyPressed(int key);
    static bool isKeyToggled(int key);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static bool isMouseButtonPressed(int button);
    static bool isMouseButtonToggled(int button);
    static void getCursorPos(GLFWwindow* window, float* currMouseX, float* currMouseY);

private:
    static std::unordered_map<int, bool> keyStates;
    static std::unordered_map<int, bool> toggledStates;
    static std::unordered_map<int, bool> mouseButtonStates;
    static std::unordered_map<int, bool> mouseButtonToggledStates;
};
