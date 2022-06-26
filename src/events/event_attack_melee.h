#ifndef EVENT_ATACK_H
#define EVENT_ATACK_H

#include <iostream>

#include <GLFW/glfw3.h>

#include "event.h"
#include "event_handler.h"
#include "../entity_management/entity_manager.h"

class EventAttack : public Event {
private:
    std::shared_ptr<EntityManager> entity_manager;
    EventManager& event_handler;
    int parent_id;

public:
    EventAttack(std::shared_ptr<EntityManager> entity_manager, EventManager& event_handler, int parent_id) : event_handler(event_handler) {
        this->entity_manager = entity_manager;
        this->parent_id = parent_id;
    }

    void execute() {
        int sword = this->entity_manager->createEntity();
        float height = this->entity_manager->getRenderable(parent_id).height + (this->entity_manager->getRenderable(parent_id).scale.y/2);
        this->entity_manager->setRenderable(sword, glm::vec2(0.0f, 10.0f), height, { "res/sword_sweep.png" }, "flat_square", this->parent_id);
        this->entity_manager->setExpiration(sword, 0.5f);

        // for (auto& [id, collision_area] : entity_manager->hitAreas) {
        //     std::cout << entity_manager->getEntity(id).name << "\n";
        // }
    }
};


#endif