#include "GLFW/glfw3.h"
#include "input_handler.h"
#include "action.h"
#include <unordered_map>

class Actions {
public:
    Actions(InputHandler& inputHandler);
    Action getCurrentAction();

private:
    InputHandler& inputHandler;                       
    std::unordered_map<int, Action> keyBindings;   
};
