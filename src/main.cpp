#include <iostream>
#include <string>
#include <cstring>

#include "states/state.h"
#include "window_stuff/window.h"
#include "window_stuff/inputs.h"


int main() {
    Window window = Window();
    Inputs inputs = Inputs(window.getGlfwWindow());

    State state = State(window, inputs);

    while (!window.shouldClose()) {
        window.performance_counter();
        state.step(window, inputs);
    }

    glfwTerminate();
    return 0;
}
