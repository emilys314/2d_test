#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_loader.h"

int create_player(Entity_Manager &entity_manager, glm::vec2 pos) {
    std::vector<unsigned int> textures_player = {load_texture_2d("res/player.png")};
    std::vector<unsigned int> textures_player_right = {load_texture_2d("res/player_side.png")};
    std::vector<unsigned int> textures_player_left = {load_texture_2d("res/player_side_flip.png")};
    std::vector<unsigned int> textures_player_up = {load_texture_2d("res/player_up.png")};

    int player = entity_manager.createEntity();
    entity_manager.setRenderable(player, pos, 0.5f, textures_player, glm::vec2(2.0f, 2.0f));
    entity_manager.setDirectional(player, textures_player, textures_player_left, textures_player_right, textures_player_up, SOUTH);
    entity_manager.setPlayer(player, true);
    entity_manager.setBoundingBox(player, -8.0f, 8.0f, -16.0f, 0.0f);
    entity_manager.setMovement(player, glm::vec2(0.0f, 0.0f), 50.0f, 1.0f);

    return player;
}

#endif
