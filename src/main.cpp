#include <iostream>

#include "window_stuff/window.h"
#include "window_stuff/inputs.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "logic_stuff/actions.h"


int main() {
    Window window = Window();
    Inputs inputs = Inputs(window.getGlfwWindow());
    Renderer renderer = Renderer(window);
    Actions actions = Actions();

    Camera camera = Camera();

    //// render loop ////
    while (!window.shouldClose()) {
        actions.processCamera(window.getGlfwWindow(), inputs, camera);
        renderer.render(window, inputs, camera);
        
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
