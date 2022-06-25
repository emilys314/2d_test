#ifndef EVENT_ATACK_H
#define EVENT_ATACK_H

#include "event.h"
#include "../entity_management/entity_manager.h"
#include "event_manager.h"
#include <GLFW/glfw3.h>

class EventAttack : public Event {
private:
    std::shared_ptr<Entity_Manager> entity_manager;
    EventManager& event_manager;

public:
    EventAttack(std::shared_ptr<Entity_Manager> entity_manager, EventManager& event_manager, int parent_id) : event_manager(event_manager) {
        // printf("EventAttack()\n");
        this->entity_manager = entity_manager;
    }

    void execute() {
        // printf("EventAttack execute()\n");
        int sword = this->entity_manager->createEntity();
        this->entity_manager->setRenderable(sword, glm::vec2(8.0f, 0.0f), 0.9f, {"res/sword_sweep.png"}, "flat_square", this->entity_manager->player);
        this->entity_manager->setExpiration(sword, 1.0f);

        // event_manager.add_event(new EventExpire())
        // std::unique_ptr<Event> attack(new EventExpire(entity_manager, sword, 1.0));
        // event_manager.add_regular_event(std::move(attack));
    }
};


#endif