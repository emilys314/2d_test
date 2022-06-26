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
#include "../entity_management/collision_area.h"
#include "../window_stuff/inputs.h"

void processMovementCollisions(Timer timer, Inputs& inputs, std::shared_ptr<EntityManager> entity_manager) {
    float delta = timer.getDeltaTime();

    // for each entity that has movement property
    for (auto& [a, a_movement] : entity_manager->movements) {
        // if a is moving
        if (a_movement.velocity != glm::vec2(0.0f, 0.0f)) {
            glm::vec2 a_desired_velocity = entity_manager->getMovement(a).velocity * delta;
            // if a has collision
            auto a_collision_area_iterator = entity_manager->collision_areas.find(a);
            if (a_collision_area_iterator != entity_manager->collision_areas.end()) {
                // for each other entity with collisions
                for (auto& [b, b_collision_area] : entity_manager->collision_areas) {
                    CollisionArea a_new_collision_area = a_collision_area_iterator->second;
                    a_new_collision_area.offsetBy(a_desired_velocity);

                    // check if a intersects with b
                    if (a_new_collision_area.intersects(b_collision_area) && a != b) {
                        // resolve the desired velocity of a to one that is valid
                        a_desired_velocity = a_new_collision_area.resolveGoingInto(b_collision_area, a_desired_velocity);
                    }
                }
                entity_manager->getCollisionArea(a).offsetBy(a_desired_velocity);
            }
            entity_manager->getMovement(a).velocity = (a_desired_velocity);
            entity_manager->getRenderable(a).position += (a_desired_velocity);
        }
    }
}

void updateDirections(std::shared_ptr<EntityManager> entity_manager) {
    for (auto const& [id, directional] : entity_manager->directionals) {
        if (directional.direction == SOUTH)
            entity_manager->getRenderable(id).textures = directional.south_textures;
        if (directional.direction == WEST)
            entity_manager->getRenderable(id).textures = directional.west_textures;
        if (directional.direction == EAST)
            entity_manager->getRenderable(id).textures = directional.east_textures;
        if (directional.direction == NORTH)
            entity_manager->getRenderable(id).textures = directional.north_textures;
    }
}


#endif
