#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputHandler {
public:
    static void init(GLFWwindow* window);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static bool isKeyPressed(int key);
    static bool isKeyToggled(int key); 

private:
    static std::unordered_map<int, bool> keyStates;
    static std::unordered_map<int, bool> toggledStates;
};
