#include <iostream>

#include "scene_stuff/scene.h"
#include "window_stuff/window.h"
#include "window_stuff/inputs.h"

int main() {
    Window window = Window();
    Inputs inputs = Inputs(window.getGlfwWindow());

    Scene scene = Scene(window);
    // Camera camera = Camera();

    //// render loop ////
    while (!window.shouldClose()) {
        scene.do_stuff(window, inputs);
        
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
