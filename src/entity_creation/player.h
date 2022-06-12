#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_manager.h"

int create_player(Entity_Manager &entity_manager, glm::vec2 pos) {
    int player = entity_manager.createEntity("player");
    entity_manager.player = player;
    entity_manager.setRenderable(player, pos, 16.0f, {"res/player/player.png"}, "angled_square");
    entity_manager.setDirectional(player, {"res/player/player.png"}, {"res/player/player_side_flip.png"}, {"res/player/player_side.png"}, {"res/player/player_up.png"}, SOUTH);
    entity_manager.setBoundingBox(player, -8.0f, 8.0f, -16.0f, 0.0f);
    entity_manager.setMovement(player, glm::vec2(0.0f, 0.0f), 50.0f, 1.0f);

    // entity_manager.setAction(player, "")


    // auto attack = [](Entity_Manager entity_manager) {
    //     printf("Attack");

    //     std::vector<Texture> sword_textures = { load_texture_2d("res/sword.png") };
    //     int sword = entity_manager.createEntity();
    //     entity_manager.setRenderable(sword, glm::vec2(8.0f, 0.0f), 0.5f, sword_textures, entity_manager.player);
    // };

    // entity_manager.setAttack(player, {"res/sword_sweep.png"});
    
    return player;
}

#endif
