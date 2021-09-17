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
    float speed = 2.5f * timer.getDeltaTime();

    glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
    if (inputs.getKey(GLFW_KEY_W) >= GLFW_PRESS) {
        direction += glm::vec3(0.0f, 1.0f, 0.0f);
        entity_manager.getDirectional(id).direction = NORTH;
    }
    if (inputs.getKey(GLFW_KEY_S) >= GLFW_PRESS) {
        direction -= glm::vec3(0.0f, 1.0f, 0.0f);
        entity_manager.getDirectional(id).direction = SOUTH;
    }
    if (inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS) {
        direction -= glm::vec3(1.0f, 0.0f, 0.0f);
        entity_manager.getDirectional(id).direction = WEST;
    }
    if (inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS) {
        direction += glm::vec3(1.0f, 0.0f, 0.0f);
        entity_manager.getDirectional(id).direction = EAST;
    }

    if (glm::length(direction) > 1) 
        direction = glm::normalize(direction);
    entity_manager.getSquare(id).position += direction * speed;
}

void updateDirections(Entity_Manager &entity_manager) {
    for (auto const& [id, directional] : entity_manager.getDirectionals()) {
        if (directional.direction == SOUTH)
            entity_manager.getSquare(id).texture = directional.south_texture;
        if (directional.direction == WEST)
            entity_manager.getSquare(id).texture = directional.west_texture;
        if (directional.direction == EAST)
            entity_manager.getSquare(id).texture = directional.east_texture;
        if (directional.direction == NORTH)
            entity_manager.getSquare(id).texture = directional.north_texture;
    }
}

#endif
