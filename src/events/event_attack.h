#ifndef EVENT_ATACK_H
#define EVENT_ATACK_H

#include "event.h"
#include "../entity_management/entity_manager.h"

class EventAttack : public Event {
private:
    // Entity_Manager entity_manager;

public:
    EventAttack(Entity_Manager &entity_manager, int parent_id) {
        // this->entity_manager = entity_manager;
    }

    void execute(Entity_Manager &entity_manager) {
        printf("EventAttack\n");

        int sword = entity_manager.createEntity();
        entity_manager.setRenderable(sword, glm::vec2(8.0f, 0.0f), 0.9f, {"res/sword_sweep.png"}, "flat_square", entity_manager.player);
        entity_manager.setExpiration(sword, 1.0f);
    }
};


#endif