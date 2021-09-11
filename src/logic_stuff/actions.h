#ifndef ACTIONS_H
#define ACTIONS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../window_stuff/inputs.h"
#include "../graphics/camera.h"

class Actions {
private:
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

public:
    void processCamera(GLFWwindow *window, Inputs &inputs, Camera &camera) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (inputs.getKey(GLFW_KEY_ESCAPE) >= GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        float cameraSpeed = 2.5f * deltaTime;
        if (inputs.getKey(GLFW_KEY_W) >= GLFW_PRESS)
            camera.setPosition(camera.getPosition() + glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed);
        if (inputs.getKey(GLFW_KEY_S) >= GLFW_PRESS)
            camera.setPosition(camera.getPosition() - glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed);
        if (inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS)
            camera.setPosition(camera.getPosition() - glm::vec3(1.0f, 0.0f, 0.0f) * cameraSpeed);
        if (inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS)
            camera.setPosition(camera.getPosition() + glm::vec3(1.0f, 0.0f, 0.0f) * cameraSpeed);
    }
};

#endif