#ifndef PLAYERABLE_CHARACTER_H
#define PLAYERABLE_CHARACTER_H

#include <stdio.h>
#include "parent_driver.h"
#include "../events/event_handler.h"
#include "../events/event_attack.h"
#include "../window_stuff/inputs.h"

class PlayableCharacter : public Driver {
private:
    std::shared_ptr<EntityManager> entity_manager;
    EventManager& event_handler;
    Inputs& inputs;
    int last_mouse_button_left = 0;

public:
    PlayableCharacter(std::shared_ptr<EntityManager> entity_manager, EventManager& event_handler, Inputs& inputs) :
            event_handler(event_handler), inputs(inputs) {
        this->entity_manager = entity_manager;
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
    }
};

#endif