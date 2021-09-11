#include <iostream>

#include "state_stuff/state.h"
#include "window_stuff/window.h"
#include "window_stuff/inputs.h"

int main() {
    Window window = Window();
    Inputs inputs = Inputs(window.getGlfwWindow());

    State state = State(window);

    //// render loop ////
    while (!window.shouldClose()) {
        state.do_stuff(window, inputs);
        
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
