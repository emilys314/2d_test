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
#include "../logic/attack.h"
#include "../logic/expirable.h"
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

    Entity_Manager entity_manager = Entity_Manager();
    int main_cam;
    int player;

public:
    State(Window window) {
        std::cout << "Created State\n";
        renderer = Renderer(window);
        timer = Timer();

        // PLAYER
        player = create_player(entity_manager, glm::vec2(0.0f, 0.0f));


        // BEAR
        // std::vector<Texture> bear_textures = { load_texture_2d("res/bear.png") };
        // std::vector<char*> bear_texture_paths = {"res/bear.png"};
        int bear = entity_manager.createEntity("bear");
        entity_manager.setRenderable(bear, glm::vec2(0.0f, 32.0f), 1.5f, {"res/bear.png"}, "flat_square");

        // GRASS FLOOR
        // std::vector<Texture> textures_grass = { load_texture_2d("res/grass_16.png") };
        // std::vector<char*> bear_texture_paths = {"res/grass_16.png"}
        for (int x = -20; x <= 20; x++) {
            for (int y = -20; y <= 20; y++) {
                int id = entity_manager.createEntity("grass");
                entity_manager.setRenderable(id, glm::vec2(x * 16, y * 16), 0.0f, {"res/grass_16.png"}, "flat_square");
            }
        }

        int rock1 = create_rock(entity_manager, glm::vec2(1.0f, 3.0f));
        int rock2 = create_rock(entity_manager, glm::vec2(-3.0f, -3.0f));

        main_cam = entity_manager.createEntity("camera");
        entity_manager.setCamera(main_cam, glm::vec3(0.0f, 0.0f, 101.0f));

    }

    void step(Window& window, Inputs& inputs) {
        timer.setTime();
        proceessExpirables(entity_manager, timer);
        processPlayerInput(timer, inputs, entity_manager, player);
        processMovementCollisions(timer, inputs, entity_manager, player);
        updateCameraPosition(entity_manager, main_cam, player);
        updateDirections(entity_manager);
        proceessAttacks(entity_manager, inputs);
        renderer.render(window, main_cam, entity_manager);

        if (inputs.getKey(GLFW_KEY_ESCAPE) >= GLFW_PRESS)
            glfwSetWindowShouldClose(window.glfwwindow, true);
    }

    Entity_Manager& getEntities() {
        return entity_manager;
    }
};

#endif
