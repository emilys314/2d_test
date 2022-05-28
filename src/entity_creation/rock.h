#ifndef ROCK_H
#define ROCK_H

#include <vector>
#include <string>

#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_loader.h"

int create_rock(Entity_Manager &entity_manager, glm::vec2 pos) {
    int rock = entity_manager.createEntity("rock");
    entity_manager.setRenderable(rock, glm::vec2(pos.x * 16, pos.y * 16), 0.4f, {"res/rock.png"}, "flat_square");
    entity_manager.setBoundingBox(rock, -7.0f, 7.0f, -7.0f, 7.0f);

    return rock;
}

#endif
