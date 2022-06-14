#ifndef EVENT_ATACK_H
#define EVENT_ATACK_H

#include "event.h"
#include "../entity_management/entity_manager.h"
#include "event_manager.h"
#include <GLFW/glfw3.h>

class EventAttack : public Event {
private:
    Entity_Manager& entity_manager;
    EventManager& event_manager;

public:
    EventAttack(Entity_Manager &entity_manager, EventManager& event_manager, int parent_id) : entity_manager(entity_manager), event_manager(event_manager) {
        // this->entity_manager = entity_manager;
    }

    void execute() {
        printf("EventAttack\n");

        int sword = entity_manager.createEntity();
        this->entity_manager.setRenderable(sword, glm::vec2(8.0f, 0.0f), 0.9f, {"res/sword_sweep.png"}, "flat_square", this->entity_manager.player);
        this->entity_manager.setExpiration(sword, 1.0f);

        // event_manager.add_event(new EventExpire())
        // std::unique_ptr<Event> attack(new EventExpire(entity_manager, sword, 1.0));
        // event_manager.add_regular_event(std::move(attack));
    }
};


#endif