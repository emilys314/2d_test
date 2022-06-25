#ifndef EVENT_ATACK_H
#define EVENT_ATACK_H

#include "event.h"
#include "../entity_management/entity_manager.h"
#include "event_handler.h"
#include <GLFW/glfw3.h>

class EventAttack : public Event {
private:
    std::shared_ptr<EntityManager> entity_manager;
    EventManager& event_handler;

public:
    EventAttack(std::shared_ptr<EntityManager> entity_manager, EventManager& event_handler, int parent_id) : event_handler(event_handler) {
        // printf("EventAttack()\n");
        this->entity_manager = entity_manager;
    }

    void execute() {
        // printf("EventAttack execute()\n");
        int sword = this->entity_manager->createEntity();
        this->entity_manager->setRenderable(sword, glm::vec2(8.0f, 0.0f), 0.9f, {"res/sword_sweep.png"}, "flat_square", this->entity_manager->player);
        this->entity_manager->setExpiration(sword, 1.0f);

        // event_handler.add_event(new EventExpire())
        // std::unique_ptr<Event> attack(new EventExpire(entity_manager, sword, 1.0));
        // event_handler.addRegularEvent(std::move(attack));
    }
};


#endif