#ifndef ATTACK_H
#define ATTACK_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../entity_management/entity_manager.h"
#include "../res_loader/texture_manager.h"
#include "../window_stuff/inputs.h"

int last_mouse_button_left = 0;

void proceessAttacks(Entity_Manager& entity_manager, Inputs &inputs) {
    if(inputs.getMouseButton(GLFW_MOUSE_BUTTON_LEFT) > 0 && last_mouse_button_left == 0) {
        printf("Attack");

        int sword = entity_manager.createEntity();
        entity_manager.setRenderable(sword, glm::vec2(8.0f, 0.0f), 0.9f, {"res/sword_sweep.png"}, "square", entity_manager.player);
        entity_manager.setExpiration(sword, 1.0f);
    }

    last_mouse_button_left = inputs.getMouseButton(GLFW_MOUSE_BUTTON_LEFT);
}


#endif