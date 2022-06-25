#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <memory>

#include "../drivers/playable_character.h"
#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_manager.h"
#include "../events/event_manager.h"
#include "../window_stuff/inputs.h"

int create_player(std::shared_ptr<Entity_Manager> entity_manager, EventManager& event_manager, Inputs& inputs, glm::vec2 pos) {
    int player = entity_manager->createEntity("player");
    entity_manager->player = player;
    entity_manager->setRenderable(player, pos, 16.0f, { "res/player/player.png" }, "angled_square");
    entity_manager->setDirectional(player, { "res/player/player.png" }, { "res/player/player_side_flip.png" }, { "res/player/player_side.png" }, { "res/player/player_up.png" }, SOUTH);
    entity_manager->setBoundingBox(player, -8.0f, 8.0f, -16.0f, 0.0f);
    entity_manager->setMovement(player, glm::vec2(0.0f, 0.0f), 50.0f, 1.0f);

    std::shared_ptr<Driver> pc(new PlayableCharacter(entity_manager, event_manager, inputs));
    entity_manager->setDriver(player, std::move(pc));


    return player;
}

#endif
