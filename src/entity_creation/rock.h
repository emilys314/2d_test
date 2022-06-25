#ifndef ROCK_H
#define ROCK_H

#include <vector>
#include <string>

#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_manager.h"

int create_rock(std::shared_ptr<EntityManager> entity_manager, glm::vec2 pos) {
    int rock = entity_manager->createEntity("rock");
    entity_manager->setRenderable(rock, glm::vec2(pos.x * 16, pos.y * 16), 16.0f, {"res/rock.png"}, "angled_square");
    entity_manager->setBoundingBox(rock, -7.0f, 7.0f, -7.0f, 7.0f);

    return rock;
}

#endif
