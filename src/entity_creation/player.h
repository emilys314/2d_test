#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <memory>

#include "../drivers/playable_character.h"
#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_manager.h"

int create_player(Entity_Manager &entity_manager, glm::vec2 pos) {
    int player = entity_manager.createEntity("player");
    entity_manager.player = player;
    entity_manager.setRenderable(player, pos, 16.0f, {"res/player/player.png"}, "angled_square");
    entity_manager.setDirectional(player, {"res/player/player.png"}, {"res/player/player_side_flip.png"}, {"res/player/player_side.png"}, {"res/player/player_up.png"}, SOUTH);
    entity_manager.setBoundingBox(player, -8.0f, 8.0f, -16.0f, 0.0f);
    entity_manager.setMovement(player, glm::vec2(0.0f, 0.0f), 50.0f, 1.0f);

    std::shared_ptr<Driver> attack(new PlayableCharacter());

    // PlayableCharacter pc = PlayableCharacter();
    // std::unique_ptr<Event> attack(new EventAttack(entity_manager, event_manager, entity_manager.player));
    // event_manager.add_regular_event(std::move(attack));
    entity_manager.setDriver(player, std::move(attack));

    
    return player;
}

#endif
