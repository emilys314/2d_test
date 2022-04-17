// #ifndef ACTIONS_H
// #define ACTIONS_H

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include "../window_stuff/inputs.h"
// #include "../window_stuff/window.h"

// class Actions {
// private:
//     float deltaTime = 0.0f; // Time between current frame and last frame
//     float lastFrame = 0.0f; // Time of last frame

//     int move_up = GLFW_KEY_W;
//     int move_down = GLFW_KEY_S;
//     int move_left = GLFW_KEY_A;
//     int move_right = GLFW_KEY_D;



// public:
    

//     void processCamera(Window& window, Inputs &inputs, glm::vec3 &cam_pos) {
//         float currentFrame = glfwGetTime();
//         deltaTime = currentFrame - lastFrame;
//         lastFrame = currentFrame;

        
        
//         if (move_up) {

//         }
//     }

//     void processMovementInput(Inputs &inputs) {
//         int input_move_up = GLFW_KEY_W;
//         int input_move_down = GLFW_KEY_S;
//         int input_move_left = GLFW_KEY_A;
//         int input_move_right = GLFW_KEY_D;

//         // if (inputs.getKey(input_move_up)) 
//     }
// };

// #endif