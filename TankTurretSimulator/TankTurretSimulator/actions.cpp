#include "actions.h"

Actions::Actions(InputHandler& inputHandler) : inputHandler(inputHandler) {
    keyBindings[GLFW_KEY_ESCAPE] = Action::CLOSE_SIMULATION;
}

Action Actions::getCurrentAction() {
    for (const auto& pair : keyBindings) {
        int key = pair.first;
        Action action = pair.second;

        if (inputHandler.isKeyPressed(key)) {
            return action;
        }
    }
    return Action::NONE;
}
