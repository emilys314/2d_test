#ifndef EXPIRABLE_H
#define EXPIRABLE_H

#include "../entity_management/entity_manager.h"
#include "timer.h"

void proceessExpirables(Entity_Manager& entity_manager, Timer& timer) {
    double current_time = timer.getTime();

    // for (auto const &[id, expiration_time] : entity_manager.expirations) {
    //     printf("Checking %i. Current %f vs %f\n", id, current_time, expiration_time);

    //     if (current_time > expiration_time) {
    //         entity_manager.deleteEntity(id);
    //         printf("Deleting %i\n", id);
    //     }
    // }

    auto iter = entity_manager.expirations.begin();
    while (iter != entity_manager.expirations.end()) {
        printf("Checking %i. Current %f vs %f\n", iter->first, current_time, iter->second);
        if (timer.getTime() > iter->second) {
            int id = iter->first;
            ++iter;
            entity_manager.deleteEntity(id);
        } else {
            ++iter;
        }
    }

}

#endif