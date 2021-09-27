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

bool isOverlapping1D(float xmin1, float xmax1, float xmin2, float xmax2) {
    return (xmax1 >= xmin2) && (xmax2 >= xmin1);
}


void processPlayerMovement(Timer timer, Inputs &inputs, Entity_Manager &entity_manager, int player_id) {
    float speed = 32.0f * timer.getDeltaTime();

    std::cout << "speed: " << speed << "\n";

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
    }

    // if (direction.x != 0. && direction.y != 0) 
    //     direction = glm::vec2(2.83f, 2.83f);

    glm::vec2 new_position = entity_manager.getSquare(player_id).position + direction;

    float xmin1 = new_position.x + entity_manager.getBoundingBox(player_id).xmin;
    float xmax1 = new_position.x + entity_manager.getBoundingBox(player_id).xmax;
    float ymin1 = new_position.y + entity_manager.getBoundingBox(player_id).ymin;
    float ymax1 = new_position.y + entity_manager.getBoundingBox(player_id).ymax;

    bool collision = false;
    for (auto const& [id, box] : entity_manager.getBoundingBoxes()) {
        if (id != player_id) {
            float xmin2 = entity_manager.getSquare(id).position.x + box.xmin;
            float xmax2 = entity_manager.getSquare(id).position.x + box.xmax;
            float ymin2 = entity_manager.getSquare(id).position.y + box.ymin;
            float ymax2 = entity_manager.getSquare(id).position.y + box.ymax;

            bool x_overlap = isOverlapping1D(xmin1, xmax1, xmin2, xmax2);
            bool y_overlap = isOverlapping1D(ymin1, ymax1, ymin2, ymax2);

            if (isOverlapping1D(xmin1, xmax1, xmin2, xmax2) && isOverlapping1D(ymin1, ymax1, ymin2, ymax2)) {
                collision = true;
                break;
            }
                
        }
    }



    if (!collision)
        entity_manager.getSquare(player_id).position = new_position;
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
