#ifndef PROCESS_DRIVERS_H
#define PROCESS_DRIVERS_H

#include "../entity_management/entity_manager.h"

void processDrivers(std::shared_ptr<EntityManager> entity_manager) {
    for (auto& [id, driver] : entity_manager->drivers) {
        driver->check_inputs();
    }
}

#endif