#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "../entity_creation/rock.h"
#include "../entity_creation/player.h"
#include "../entity_management/entity_manager.h"
#include "../events/event_handler.h"
#include "../graphics/renderer.h"
#include "../logic/actions.h"
#include "../logic/process_drivers.h"
#include "../logic/expirable.h"
#include "../logic/movement_collision.h"
#include "../logic/timer.h"
#include "../logic/update_camera.h"
#include "../window_stuff/inputs.h"
#include "../window_stuff/window.h"

class State {
private:
    Renderer renderer;
    Timer timer;

    // Entity_Manager entity_manager = Entity_Manager();
    std::shared_ptr<EntityManager> entity_manager = std::make_shared<EntityManager>();
    int main_cam;
    int player;

    EventManager event_handler = EventManager();

public:
    State(Window window, Inputs& inputs) {
        std::cout << "Created State\n";
        renderer = Renderer(window);
        timer = Timer();

        // PLAYER
        player = createPlayer(entity_manager, event_handler, timer, inputs, glm::vec2(0.0f, 0.0f));


        // BEAR
        int bear = entity_manager->createEntity("bear");
        entity_manager->setRenderable(bear, glm::vec2(0.0f, 32.0f), 16.0f, {"res/bear.png"}, "angled_square");

        // GRASS FLOOR
        for (int x = -20; x <= 20; x++) {
            for (int y = -20; y <= 20; y++) {
                int id = entity_manager->createEntity("grass");
                entity_manager->setRenderable(id, glm::vec2(x * 16, y * 16), 0.0f, {"res/grass_16.png"}, "flat_square");
            }
        }

        int rock1 = createRock(entity_manager, glm::vec2(1.0f, 3.0f));
        int rock2 = createRock(entity_manager, glm::vec2(-3.0f, -3.0f));

        main_cam = entity_manager->createEntity("camera");
        entity_manager->setCamera(main_cam, glm::vec3(0.0f, 0.0f, 101.0f));

    }

    void step(Window& window, Inputs& inputs) {
        timer.setTime();
        proceessExpirables(entity_manager, timer);
        processMovementCollisions(timer, inputs, entity_manager, player);
        updateCameraPosition(entity_manager, main_cam, player);
        updateDirections(entity_manager);
        // proceessAttacks(entity_manager, event_handler, inputs);
        processDrivers(entity_manager);
        event_handler.runEvents(entity_manager);
        renderer.render(window, main_cam, entity_manager);

        if (inputs.getKey(GLFW_KEY_ESCAPE) >= GLFW_PRESS)
            glfwSetWindowShouldClose(window.glfwwindow, true);
    }

    std::shared_ptr<EntityManager> getEntities() {
        return entity_manager;
    }
};

#endif
