#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <queue>          // std::queue
#include <memory>

#include "event.h"
#include "../entity_management/entity_manager.h"

class EventManager {
private:
    std::queue<std::unique_ptr<Event>> event_queue = {};

public:
    EventManager() {

    }

    void add_event(std::unique_ptr<Event> event) {
        event_queue.push(std::move(event));
        // event->execute();
    }

    void run_events(Entity_Manager& entity_manager) {
        if (!event_queue.empty()) {
            event_queue.front()->execute(entity_manager);
            event_queue.pop();
        }
    }

};


#endif