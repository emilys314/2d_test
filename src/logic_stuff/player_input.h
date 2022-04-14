#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "timer.h"
#include "../entity_stuff/entity_manager.h"
#include "../window_stuff/inputs.h"

void processPlayerInput(Timer timer, Inputs &inputs, Entity_Manager &entity_manager, int player_id) {
    float speed = 64.0f * timer.getDeltaTime();

    // std::cout << "speed: " << speed << "\n";

    glm::vec2 direction = glm::vec2(0.0f, 0.0f);
    if (inputs.getKey(GLFW_KEY_W) >= GLFW_PRESS) {
        direction += glm::vec2(0.0f, speed);
        entity_manager.getDirectional(player_id).direction = NORTH;
    }
    if (inputs.getKey(GLFW_KEY_S) >= GLFW_PRESS) {
        direction -= glm::vec2(0.0f, speed);
        entity_manager.getDirectional(player_id).direction = SOUTH;
    }
    if (inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS) {
        direction -= glm::vec2(speed, 0.0f);
        entity_manager.getDirectional(player_id).direction = WEST;
    }
    if (inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS) {
        direction += glm::vec2(speed, 0.0f);
        entity_manager.getDirectional(player_id).direction = EAST;
        // if (timer.getQuarterSecond()) {
        //     entity_manager.getSquare(player_id).texture_index = (entity_manager.getSquare(player_id).texture_index + 1) % 4;
        // }
    }

    if (!inputs.getKey(GLFW_KEY_W) && !inputs.getKey(GLFW_KEY_S) && !(inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS) && !(inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS)) {
        entity_manager.getSquare(player_id).texture_index = 0;
    }

    if (direction.x != 0. && direction.y != 0)
        direction *= glm::vec2(0.7, 0.7f);


    entity_manager.getMovement(player_id).velocity = direction;
}



#endif
