#ifndef PLAYERABLE_CHARACTER_H
#define PLAYERABLE_CHARACTER_H

#include <stdio.h>
#include "parent_driver.h"
#include "../events/event_handler.h"
#include "../events/event_attack.h"
#include "../logic/timer.h"
#include "../window_stuff/inputs.h"

class PlayableCharacter : public Driver {
private:
    std::shared_ptr<EntityManager> entity_manager;
    EventManager& event_handler;
    Inputs& inputs;
    Timer& timer;

    int player_id;
    int last_mouse_button_left = 0;

public:
    PlayableCharacter(int player_id, std::shared_ptr<EntityManager> entity_manager, EventManager& event_handler, Inputs& inputs, Timer& timer) :
        event_handler(event_handler), inputs(inputs), timer(timer) {
        this->entity_manager = entity_manager;
        this->player_id = player_id;
        printf("PlayableCharacter created\n");
    }

    void checkInputs() {
        // printf("PlayableCharacter check_input\n");
        if (inputs.getMouseButton(GLFW_MOUSE_BUTTON_LEFT) > 0 && last_mouse_button_left == 0) {
            printf("Driver proceessAttacks\n");
            std::unique_ptr<Event> attack(new EventAttack(entity_manager, event_handler, entity_manager->player));
            event_handler.addRegularEvent(std::move(attack));
        }
        last_mouse_button_left = inputs.getMouseButton(GLFW_MOUSE_BUTTON_LEFT);

        float speed = 64.0f * timer.getDeltaTime();

        glm::vec2 direction = glm::vec2(0.0f, 0.0f);
        if (inputs.getKey(GLFW_KEY_W) >= GLFW_PRESS) {
            direction += glm::vec2(0.0f, speed);
            entity_manager->getDirectional(player_id).direction = NORTH;
        }
        if (inputs.getKey(GLFW_KEY_S) >= GLFW_PRESS) {
            direction -= glm::vec2(0.0f, speed);
            entity_manager->getDirectional(player_id).direction = SOUTH;
        }
        if (inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS) {
            direction -= glm::vec2(speed, 0.0f);
            entity_manager->getDirectional(player_id).direction = WEST;
        }
        if (inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS) {
            direction += glm::vec2(speed, 0.0f);
            entity_manager->getDirectional(player_id).direction = EAST;
        }

        if (!inputs.getKey(GLFW_KEY_W) && !inputs.getKey(GLFW_KEY_S) && !(inputs.getKey(GLFW_KEY_A) >= GLFW_PRESS) && !(inputs.getKey(GLFW_KEY_D) >= GLFW_PRESS)) {
            entity_manager->getRenderable(player_id).texture_index = 0;
        }

        if (direction.x != 0. && direction.y != 0) {
            direction *= glm::vec2(0.7, 0.7f);
        }

        entity_manager->getMovement(player_id).velocity = direction;

    }
};

#endif