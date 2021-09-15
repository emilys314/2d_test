#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <map>

#include "../entity_stuff/entity_manager.h"
#include "../graphics/renderer.h"
#include "../logic_stuff/actions.h"
#include "../logic_stuff/player_movement.h"
#include "../logic_stuff/timer.h"
#include "../logic_stuff/update_camera.h"
#include "../window_stuff/inputs.h"
#include "../window_stuff/window.h"

class State {
private:
    Renderer renderer;
    Timer timer;
    Actions actions;

    Entity_Manager entity_manager = Entity_Manager();
    int main_cam;
    int player;

public:
    State(Window window) {
        renderer = Renderer(window);
        timer = Timer();
        actions = Actions();

        unsigned int tex_player = load_texture_2d("res/player.png");
        player = entity_manager.createEntity();
        entity_manager.setSquare(player, glm::vec3(0.0f, 0.0f, 0.5f), tex_player);
        entity_manager.setPlayer(player, true);

        unsigned int texture = load_texture_2d("res/cave_rock.png");
        for (int x = -6; x <=6; x++) {
            for (int y = -6; y <=6; y++) {
                int id = entity_manager.createEntity();
                entity_manager.setSquare(id, glm::vec3(x, y, 0.0f), texture);
            }
        }

        main_cam = entity_manager.createEntity("camera");
        entity_manager.setCamera(main_cam, glm::vec3(0.0f, 0.0f, 1.0f));

    }

    void do_stuff(Window &window, Inputs &inputs) {
        timer.setTime();
        processPlayerMovement(timer, inputs, entity_manager, player);
        updateCameraPosition(entity_manager, main_cam, player);
        actions.processCamera(window.getGlfwWindow(), inputs, entity_manager.getCamera(main_cam));
        renderer.render(window, main_cam, entity_manager);
    }

    Entity_Manager &getEntities() {
        return entity_manager;
    }
};

#endif
