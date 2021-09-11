#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../entity_stuff/entity_manager.h"
#include "../graphics/camera.h"

class Scene {
private:
    Camera cam = Camera();

    Entity_Manager entity_manager = Entity_Manager();

public:
    Scene() {
        unsigned int texture = load_texture_2d("res/wall.jpg");

        int first = entity_manager.createEntity("first");
        entity_manager.setModel(first, glm::vec3(0.0f, 0.0f, 0.0f), texture);

        int second = entity_manager.createEntity("");
        entity_manager.setModel(second, glm::vec3(2.0f, 0.0f, 0.0f), texture);
    }

    Entity_Manager &getEntities() {
        return entity_manager;
    }
};

#endif