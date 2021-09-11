#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <map>

#include "../entity_stuff/entity_manager.h"
#include "../graphics/camera.h"
#include "../graphics/renderer.h"
#include "../logic_stuff/actions.h"
#include "../window_stuff/inputs.h"
#include "../window_stuff/window.h"

class Scene {
private:
    Camera cam = Camera();
    Renderer renderer;
    Actions actions;

    Entity_Manager entity_manager = Entity_Manager();

public:
    Scene(Window window) {
        renderer = Renderer(window);
        actions = Actions();

        unsigned int texture = load_texture_2d("res/wall.jpg");
        int first = entity_manager.createEntity("first");
        entity_manager.setModel(first, glm::vec3(0.0f, 0.0f, 0.0f), texture);
        int second = entity_manager.createEntity("");
        entity_manager.setModel(second, glm::vec3(2.0f, 0.0f, 0.0f), texture);
    }

    void do_stuff(Window &window, Inputs &inputs) {
        actions.processCamera(window.getGlfwWindow(), inputs, cam);
        renderer.render(window, cam, entity_manager);
    }

    Entity_Manager &getEntities() {
        return entity_manager;
    }
};

#endif