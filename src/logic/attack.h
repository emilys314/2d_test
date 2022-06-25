#ifndef ATTACK_H
#define ATTACK_H

#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../entity_management/entity_manager.h"
#include "../events/event_manager.h"
#include "../events/event_attack.h"
#include "../res_loader/texture_manager.h"
#include "../window_stuff/inputs.h"

int last_mouse_button_left = 0;

void proceessAttacks(Entity_Manager& entity_manager, EventManager& event_manager, Inputs &inputs) {
    if(inputs.getMouseButton(GLFW_MOUSE_BUTTON_LEFT) > 0 && last_mouse_button_left == 0) {
        printf("proceessAttacks\n");
        std::unique_ptr<Event> attack(new EventAttack(entity_manager, event_manager, entity_manager.player));
        event_manager.add_regular_event(std::move(attack));
    }

    last_mouse_button_left = inputs.getMouseButton(GLFW_MOUSE_BUTTON_LEFT);
}


#endif