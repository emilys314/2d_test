#ifndef DRIVER_CAMERA_H
#define DRIVER_CAMERA_H

#include <stdio.h>

#include "parent_driver.h"
#include "../entity_management/entity_manager.h"

class DriverCamera : public Driver {
private:
    std::shared_ptr<EntityManager> entity_manager;

    int camera_id;
    int player_id;

public:
    DriverCamera(std::shared_ptr<EntityManager> entity_manager, int camera_id, int player_id) {
        this->entity_manager = entity_manager;
        this->camera_id = camera_id;
        this->player_id = player_id;

    }

    void checkInputs() {
        entity_manager->getCamera(camera_id) = glm::vec3(entity_manager->getRenderable(player_id).position, entity_manager->getCamera(camera_id).z);
    }
};

#endif