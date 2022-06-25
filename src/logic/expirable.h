#ifndef EXPIRABLE_H
#define EXPIRABLE_H

#include "../entity_management/entity_manager.h"
#include "timer.h"

void proceessExpirables(std::shared_ptr<Entity_Manager> entity_manager, Timer& timer) {

    auto iter = entity_manager->expirations.begin();
    while (iter != entity_manager->expirations.end()) {
        // printf("Checking %i. Current %f vs %f\n", iter->first, timer.getTime(), iter->second);
        if (timer.getTime() > iter->second) {
            int id = iter->first;
            ++iter;
            entity_manager->deleteEntity(id);
        } else {
            ++iter;
        }
    }

}

#endif