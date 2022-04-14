#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../entity_creation/rock.h"
#include "../entity_creation/player.h"
#include "../entity_management/entity_manager.h"
#include "../graphics/renderer.h"
#include "../logic/actions.h"
#include "../logic/movement_collision.h"
#include "../logic/player_input.h"
#include "../logic/timer.h"
#include "../logic/update_camera.h"
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

        // PLAYER
        player = create_player(entity_manager, glm::vec2(0.0f, 0.0f));

        // BEAR
        std::vector<unsigned int> textures_bear = { load_texture_2d("res/bear.png") };
        int bear = entity_manager.createEntity();
        entity_manager.setSquare(bear, glm::vec2(0.0f, 32.0f), 0.5f, textures_bear, glm::vec2(2.0f, 2.0f));

        // GRASS FLOOR
        std::vector<unsigned int> textures_grass = { load_texture_2d("res/grass_16.png") };
        for (int x = -20; x <= 20; x++) {
            for (int y = -20; y <= 20; y++) {
                int id = entity_manager.createEntity();
                entity_manager.setSquare(id, glm::vec2(x * 16, y * 16), 0.0f, textures_grass);
            }
        }

        int rock1 = create_rock(entity_manager, glm::vec2(1.0f, 3.0f));
        int rock2 = create_rock(entity_manager, glm::vec2(-3.0f, -3.0f));

        main_cam = entity_manager.createEntity("camera");
        entity_manager.setCamera(main_cam, glm::vec3(0.0f, 0.0f, 1.0f));

    }

    void do_stuff(Window& window, Inputs& inputs) {
        timer.setTime();
        processPlayerInput(timer, inputs, entity_manager, player);
        processMovementCollisions(timer, inputs, entity_manager, player);
        updateCameraPosition(entity_manager, main_cam, player);
        updateDirections(entity_manager);
        actions.processCamera(window.getGlfwWindow(), inputs, entity_manager.getCamera(main_cam));
        renderer.render(window, main_cam, entity_manager);
    }

    Entity_Manager& getEntities() {
        return entity_manager;
    }
};

#endif
