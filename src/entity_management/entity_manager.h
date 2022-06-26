#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "collision_area.h"
#include "../drivers/parent_driver.h"
#include "../graphics/texture.h"
#include "../res_loader/model_manager.h"
#include "../res_loader/texture_manager.h"

struct Entity {
    std::string name = "";
};

struct Renderable {
    glm::vec2 position = { 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    float height;
    std::vector<Texture> textures;
    int texture_index = 0;
    Model model;
    int parent = -1;
};

enum Directions {
    SOUTH = 0,
    WEST = 1,
    EAST = 2,
    NORTH = 3
};

struct Directional {
    std::vector<Texture> south_textures;
    std::vector<Texture> west_textures;
    std::vector<Texture> east_textures;
    std::vector<Texture> north_textures;
    int direction = SOUTH;
};

struct Movement {
    glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
    float weight = 100.0f;
    float friction = 1.0f;
};

class EntityManager {
private:
    int next_id = 1;

    ModelManager model_manager = ModelManager();
    Texture_Manager texture_manager = Texture_Manager();

public:
    int player = -1;

    std::unordered_map<int, Entity> entity_ids = {};
    std::unordered_map<int, Renderable> renderables = {};
    std::unordered_map<int, glm::vec3> cameras = {};
    std::unordered_map<int, Directional> directionals = {};
    std::unordered_map<int, CollisionArea> collision_areas = {};
    std::unordered_map<int, CollisionArea> hitAreas = {};
    std::unordered_map<int, Movement> movements = {};
    std::unordered_map<int, double> expirations = {};     // TODO chagne to more efficient data structure
    std::unordered_map<int, std::shared_ptr<Driver>> drivers = {};

    EntityManager() {}

    //// Entity ////
    int createEntity(std::string name = "") {
        Entity entity = { name };
        entity_ids.emplace(next_id, entity);
        return next_id++;
    }

    Entity getEntity(int id) {
        return entity_ids[id];
    }

    void deleteEntity(int id) {
        entity_ids.erase(id);
        renderables.erase(id);
        cameras.erase(id);
        directionals.erase(id);
        collision_areas.erase(id);
        hitAreas.erase(id);
        movements.erase(id);
        expirations.erase(id);
        drivers.erase(id);

        printf("Erased %i\n", id);
    }

    //TODO: delete and reuse deleted id's

    //// Square ////
    Renderable& setRenderable(int id, glm::vec2 pos, float height, std::vector<const char*> texture_paths, std::string model, int parent = 0) {
        std::vector<Texture> textures = texture_manager.get(texture_paths);
        glm::vec3 scale = { textures[0].width, textures[0].height, textures[0].height };
        Renderable square = { pos, scale, height, textures, 0, model_manager.get(model), parent };
        renderables.emplace(id, square);
        return renderables[id];
    }

    Renderable& getRenderable(int id) {
        return renderables[id];
    }

    //// Cameras ////
    void setCamera(int id, glm::vec3 pos) {
        cameras.emplace(id, pos);
    }

    glm::vec3& getCamera(int id) {
        return cameras[id];
    }

    glm::mat4 getCameraView(int id) {
        glm::vec3 cameraPos = this->getCamera(id);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

    //// Directions ////
    void setDirectional(int id, std::vector<const char*> south_textures, std::vector<const char*> west_textures, std::vector<const char*> east_textures, std::vector<const char*> north_textures, int direction) {
        Directional dir = { texture_manager.get(south_textures), texture_manager.get(west_textures), texture_manager.get(east_textures), texture_manager.get(north_textures), direction };
        directionals.emplace(id, dir);
    }

    Directional& getDirectional(int id) {
        return directionals[id];
    }

    void setDirection(int id, int direction) {
        directionals[id].direction = direction;
    }

    //// Collision Area ////
    void setCollisionArea(int id, float x_min_rel, float x_max_rel, float y_min_rel, float y_max_rel) {
        if (this->renderables.count(id) > 0) {
            CollisionArea collision_area = CollisionArea(x_min_rel, x_max_rel, y_min_rel, y_max_rel, this->renderables[id].position);
            collision_areas.emplace(id, collision_area);
        } else {
            std::cout << "setCollisionArea expects position created for " << id << " " << this->getEntity(id).name << "\n";
        }
    }

    CollisionArea& getCollisionArea(int id) {
        return collision_areas[id];
    }

    //// Hit Area ////
    void setHitArea(int id, float x_min_rel, float x_max_rel, float y_min_rel, float y_max_rel) {
        if (this->renderables.count(id) > 0) {
            CollisionArea collision_area = CollisionArea(x_min_rel, x_max_rel, y_min_rel, y_max_rel, this->renderables[id].position);
            hitAreas.emplace(id, collision_area);
        } else {
            std::cout << "setHitArea expects position created for " << id << " " << this->getEntity(id).name << "\n";
        }
    }

    CollisionArea& getHitArea(int id) {
        return hitAreas[id];
    }

    //// Movement ////
    void setMovement(int id, glm::vec2 velocity, float weight = 50.0f, float friction = 1.0f) {
        Movement tmp = { velocity, weight, friction };
        movements.emplace(id, tmp);
    }

    Movement& getMovement(int id) {
        return movements[id];
    }

    //// Expiration ////
    void setExpiration(int id, double duration) {
        double expiration = glfwGetTime() + duration;
        expirations.emplace(id, expiration);
    }

    double getExpiration(int id) {
        return expirations[id];
    }

    // Drivers ////
    void setDriver(int id, std::shared_ptr<Driver> driver) {
        // drivers.emplace(std::move(driver));
        drivers[id] = std::move(driver);
    }


};

#endif