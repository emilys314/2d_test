#ifndef MOVEMENT_COLLISION_H
#define MOVEMENT_COLLISION_H

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "timer.h"
#include "../entity_management/entity_manager.h"
#include "../window_stuff/inputs.h"

bool isOverlapping1D(float xmin1, float xmax1, float xmin2, float xmax2) {
    return (xmax1 >= xmin2) && (xmax2 >= xmin1);
}

void processMovementCollisions(Timer timer, Inputs &inputs, Entity_Manager &entity_manager, int player_id) {
    float speed = 64.0f * timer.getDeltaTime();

    glm::vec2 new_position = entity_manager.getRenderable(player_id).position + entity_manager.getMovement(player_id).velocity;

    // bounding box points for player
    float xmin1 = new_position.x + entity_manager.getBoundingBox(player_id).xmin;
    float xmax1 = new_position.x + entity_manager.getBoundingBox(player_id).xmax;
    float ymin1 = new_position.y + entity_manager.getBoundingBox(player_id).ymin;
    float ymax1 = new_position.y + entity_manager.getBoundingBox(player_id).ymax;

    // loop through all bounding boxes
    for (auto const &[id, box] : entity_manager.boundingBoxes)
    {
        if (id != player_id)
        {
            // bounding box points for current entity
            float xmin2 = entity_manager.getRenderable(id).position.x + box.xmin;
            float xmax2 = entity_manager.getRenderable(id).position.x + box.xmax;
            float ymin2 = entity_manager.getRenderable(id).position.y + box.ymin;
            float ymax2 = entity_manager.getRenderable(id).position.y + box.ymax;

            // if the bounding boxes overlap
            if (isOverlapping1D(xmin1, xmax1, xmin2, xmax2) && isOverlapping1D(ymin1, ymax1, ymin2, ymax2))
            {
                glm::vec2 new_collision_center = glm::vec2((xmin1 + xmax1) / 2, (ymin1 + ymax1) / 2);
                glm::vec2 old_collision_center = new_collision_center - entity_manager.getMovement(player_id).velocity;
                glm::vec2 tmp_collision_center = glm::vec2((xmin2 + xmax2) / 2, (ymin2 + ymax2) / 2);

                // check if collision pair is more horizontal than vertical
                glm::vec2 diff = old_collision_center - tmp_collision_center;
                if (abs(diff.x) > abs(diff.y))
                    entity_manager.getMovement(player_id).velocity.x = 0.0f; // resolve the illegal movement
                else
                    entity_manager.getMovement(player_id).velocity.y = 0.0f;
            }
        }
    }

    entity_manager.getRenderable(player_id).position += entity_manager.getMovement(player_id).velocity;
}

void updateDirections(Entity_Manager &entity_manager) {
    for (auto const &[id, directional] : entity_manager.directionals)
    {
        if (directional.direction == SOUTH)
            entity_manager.getRenderable(id).textures = directional.south_textures;
        if (directional.direction == WEST)
            entity_manager.getRenderable(id).textures = directional.west_textures;
        if (directional.direction == EAST)
            entity_manager.getRenderable(id).textures = directional.east_textures;
        if (directional.direction == NORTH)
            entity_manager.getRenderable(id).textures = directional.north_textures;
    }
}


#endif
