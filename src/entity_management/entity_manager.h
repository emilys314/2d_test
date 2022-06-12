#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../graphics/texture.h"
#include "../res_loader/model_manager.h"
#include "../res_loader/texture_manager.h"

struct Entity {
    std::string name = "";
};

struct Renderable {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};
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

struct BoundingBox {
    float xmin, xmax;
    float ymin, ymax;
};

struct Movement {
    glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
    float weight = 100.0f;
    float friction = 1.0f;
};



class Entity_Manager {
private:
    int next_id = 1;

    Model_Manager model_manager = Model_Manager();
    Texture_Manager texture_manager = Texture_Manager();

public:
    int player = -1;
    

    std::map<int, Entity> entity_ids = {};
    std::map<int, Renderable> renderables = {};
    std::map<int, glm::vec3> cameras = {};
    std::map<int, Directional> directionals = {};
    std::map<int, BoundingBox> boundingBoxes = {};
    std::map<int, Movement> movements = {};
    // std::map<int, Attack> attacks = {};
    std::map<int, double> expirations = {};     // TODO chagne to more efficient data structure

    Entity_Manager() { }

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
        boundingBoxes.erase(id);
        movements.erase(id);
        // attacks.erase(id);
        expirations.erase(id);

        printf("Erased %i\n", id);
    }

    //TODO: delete and reuse deleted id's

    //// Square ////
    Renderable& setRenderable(int id, glm::vec2 pos, float height, std::vector<const char*> texture_paths, std::string model, int parent = 0) {
        std::vector<Texture> textures = texture_manager.get(texture_paths);
        glm::vec3 scale = {textures[0].width, textures[0].height, textures[0].height};
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

    //// Bounding Boxes ////
    void setBoundingBox(int id, float xmin, float xmax, float ymin, float ymax) {
        BoundingBox box = { xmin, xmax, ymin, ymax };
        boundingBoxes.emplace(id, box);
    }

    BoundingBox& getBoundingBox(int id) {
        return boundingBoxes[id];
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
};

#endif
