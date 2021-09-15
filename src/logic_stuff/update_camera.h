#ifndef UPDATE_CAMERA_H
#define UPDATE_CAMERA_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../entity_stuff/entity_manager.h"
#include "../window_stuff/inputs.h"

void updateCameraPosition(Entity_Manager &entity_manager, int camera_id, int player_id) {
    entity_manager.getCamera(camera_id) = entity_manager.getSquare(player_id).position;
}

#endif
