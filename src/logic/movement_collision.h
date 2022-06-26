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

bool isOverlapping1D(float xmin1, float xmax1, float xmin2, float xmax2) {
    return (xmax1 >= xmin2) && (xmax2 >= xmin1);
}

void processMovementCollisions(Timer timer, Inputs& inputs, std::shared_ptr<EntityManager> entity_manager, int player_id) {
    float delta = timer.getDeltaTime();

    // for each collision area
    for (auto& [a, a_movement] : entity_manager->movements) {
        // if it is moving
        if (a_movement.velocity != glm::vec2(0.0f, 0.0f)) {
            glm::vec2 a_desired_velocity = entity_manager->getMovement(a).velocity;
            // check for collisions
            auto a_collision_area_iterator = entity_manager->collision_areas.find(a);
            if (a_collision_area_iterator != entity_manager->collision_areas.end()) {
                for (auto& [b, b_collision_area] : entity_manager->collision_areas) {
                    // glm::vec2 a_position = entity_manager->getRenderable(a).position;
                    // glm::vec2 b_position = entity_manager->getRenderable(b).position;

                    CollisionArea a_new_collision_area = a_collision_area_iterator->second;
                    a_new_collision_area.offsetBy(a_desired_velocity * delta);

                    if (a_new_collision_area.intersects(b_collision_area) && a != b) {
                        // std::cout << "intersects" << entity_manager->getRenderable(a).position.x << " " << entity_manager->getRenderable(a).position.y << "\n";
                        // std::cout << "intersects" << entity_manager->getCollisionArea(a).x_min << " " << entity_manager->getCollisionArea(a).y_min << "\n";
                        a_desired_velocity = a_new_collision_area.resolveGoingInto(b_collision_area, a_desired_velocity);
                        std::cout << "intersects" << a_desired_velocity.x << " " << a_desired_velocity.y << "\n";

                        // entity_manager->getRenderable(a).position += (resolved_velocity * delta);
                        // entity_manager->getMovement(a).velocity = resolved_velocity * delta;
                        // entity_manager->getCollisionArea(a).offsetBy(resolved_velocity * delta);
                    }
                }
                entity_manager->getMovement(a).velocity = a_desired_velocity * delta;
                entity_manager->getRenderable(a).position += (a_desired_velocity * delta);
                entity_manager->getCollisionArea(a).offsetBy(a_desired_velocity * delta);
            }
            entity_manager->getRenderable(a).position += entity_manager->getMovement(a).velocity * delta;
            // entity_manager->getCollisionArea(player_id).offsetBy(entity_manager->getMovement(player_id).velocity);

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
