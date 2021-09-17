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
        unsigned int tex_player_right = load_texture_2d("res/player_side.png");
        unsigned int tex_player_left = load_texture_2d("res/player_left.png");
        unsigned int tex_player_up = load_texture_2d("res/player_up.png");
        player = entity_manager.createEntity();
        entity_manager.setSquare(player, glm::vec3(0.0f, 0.0f, 0.5f), tex_player, glm::vec3(2.0f, 2.0f, 1.0f));
        entity_manager.setDirectional(player, tex_player, tex_player_left, tex_player_right, tex_player_up, SOUTH);
        entity_manager.setPlayer(player, true);
        entity_manager.setBoundingBox(player, glm::vec3(-0.25f, -0.25f, 0.0f), glm::vec3(0.25f, 0.25f, 0.0f));

        unsigned int texture = load_texture_2d("res/grass_16.png");
        for (int x = -6; x <=6; x++) {
            for (int y = -6; y <=6; y++) {
                int id = entity_manager.createEntity();
                entity_manager.setSquare(id, glm::vec3(x, y, 0.0f), texture);
            }
        }

        unsigned int tex_rock = load_texture_2d("res/rock.png");
        int rock = entity_manager.createEntity();
        entity_manager.setSquare(rock, glm::vec3(2.0f, 3.0f, 0.4f), tex_rock, glm::vec3(1.0f, 1.0f, 1.0f));
        entity_manager.setBoundingBox(rock, glm::vec3(-0.25f, -0.25f, 0.0f), glm::vec3(0.25f, 0.25f, 0.0f));

        main_cam = entity_manager.createEntity("camera");
        entity_manager.setCamera(main_cam, glm::vec3(0.0f, 0.0f, 1.0f));

    }

    void do_stuff(Window &window, Inputs &inputs) {
        timer.setTime();
        processPlayerMovement(timer, inputs, entity_manager, player);
        updateCameraPosition(entity_manager, main_cam, player);
        updateDirections(entity_manager);
        actions.processCamera(window.getGlfwWindow(), inputs, entity_manager.getCamera(main_cam));
        renderer.render(window, main_cam, entity_manager);
    }

    Entity_Manager &getEntities() {
        return entity_manager;
    }
};

#endif
