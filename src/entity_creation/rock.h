#ifndef ROCK_H
#define ROCK_H

#include <vector>
#include <string>

#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_loader.h"

int create_rock(Entity_Manager &entity_manager, glm::vec2 pos) {
    std::vector<unsigned int> textures_rock = {load_texture_2d("res/rock.png")};
    int rock = entity_manager.createEntity();
    entity_manager.setRenderable(rock, glm::vec2(pos.x * 16, pos.y * 16), 0.4f, textures_rock);
    entity_manager.setBoundingBox(rock, -7.0f, 7.0f, -7.0f, 7.0f);

    return rock;
}

#endif
