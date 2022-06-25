#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <queue>          // std::queue
#include <vector>
#include <memory>

#include "event.h"
#include "../entity_management/entity_manager.h"

class EventManager {
private:
    // std::queue<std::unique_ptr<Event>> instant_queue = {};
    std::queue<std::unique_ptr<Event>> regular_queue = {};
    // std::vector<std::unique_ptr<Event>> timed_queue = {};

public:
    EventManager() {

    }

    void add_regular_event(std::unique_ptr<Event> event) {
        regular_queue.push(std::move(event));
    }

    void run_events(std::shared_ptr<Entity_Manager> entity_manager) {
        if (!regular_queue.empty()) {
            regular_queue.front()->execute();
            regular_queue.pop();
        }

    }

};


#endif