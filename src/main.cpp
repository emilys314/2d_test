#include <iostream>

#include "state_stuff/state.h"
#include "window_stuff/window.h"
#include "window_stuff/inputs.h"

void performance_counter(Window window, double lastTime, int frame_count) {
    double currentTime = glfwGetTime();
        frame_count++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
            printf("%f ms/frame\n", 1000.0/double(frame_count));
            frame_count = 0;
            lastTime += 1.0;
    }
}

int main() {
    Window window = Window();
    Inputs inputs = Inputs(window.getGlfwWindow());

    State state = State(window);

    double lastTime = glfwGetTime();
    int frame_count = 0;
    
    while (!window.shouldClose()) {
        performance_counter(window, lastTime, frame_count);
        state.do_stuff(window, inputs);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
