#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "timer.h"
#include "../entity_stuff/entity_manager.h"
#include "../window_stuff/inputs.h"


void processPlayerMovement(Timer timer, Inputs &inputs, Entity_Manager &entity_manager, int id) {

    float cameraSpeed = 2.5f * timer.getDeltaTime();
    if (inputs.getKey(GLFW_KEY_W) >= GLFW_PRESS)
        entity_manager.getSquare(id).position += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    if (inputs.getKey(GLFW_KEY_S) >= GLFW_PRESS)
        entity_manager.getSquare(id).position -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    if (inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS)
        entity_manager.getSquare(id).position -= glm::vec3(1.0f, 0.0f, 0.0f) * cameraSpeed;
    if (inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS)
        entity_manager.getSquare(id).position += glm::vec3(1.0f, 0.0f, 0.0f) * cameraSpeed;
}

#endif
