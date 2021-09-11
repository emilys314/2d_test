#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <map>

#include "../entity_stuff/entity_manager.h"
#include "../graphics/renderer.h"
#include "../logic_stuff/actions.h"
#include "../window_stuff/inputs.h"
#include "../window_stuff/window.h"

class State {
private:
    Renderer renderer;
    Actions actions;

    Entity_Manager entity_manager = Entity_Manager();
    int main_cam;

public:
    State(Window window) {
        renderer = Renderer(window);
        actions = Actions();

        unsigned int texture = load_texture_2d("res/grass.png");
        // int first = entity_manager.createEntity("first");
        // entity_manager.setSquare(first, glm::vec3(0.0f, 0.0f, 0.0f), texture);
        // int second = entity_manager.createEntity();
        // entity_manager.setSquare(second, glm::vec3(2.0f, 0.0f, 0.0f), texture);
        for (int x = -4; x <=4; x++) {
            for (int y = -4; y <=4; y++) {
                int id = entity_manager.createEntity();
                entity_manager.setSquare(id, glm::vec3(x, y, 0.0f), texture);
            }
        }

        main_cam = entity_manager.createEntity("camera");
        entity_manager.setCamera(main_cam, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void do_stuff(Window &window, Inputs &inputs) {
        actions.processCamera(window.getGlfwWindow(), inputs, entity_manager.getCamera(main_cam));
        renderer.render(window, main_cam, entity_manager);
    }

    Entity_Manager &getEntities() {
        return entity_manager;
    }
};

#endif
