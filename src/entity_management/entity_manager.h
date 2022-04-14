#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Renderable {
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    glm::vec2 scale = glm::vec2(1.0f, 1.0f);
    float height;
    // unsigned int texture;       //texture id
    std::vector<unsigned int> textures;
    int texture_index = 0;
};

enum Directions {
    SOUTH = 0,
    WEST = 1,
    EAST = 2,
    NORTH = 3
};

struct Directional {
    std::vector<unsigned int> south_textures;
    std::vector<unsigned int> west_textures;
    std::vector<unsigned int> east_textures;
    std::vector<unsigned int> north_textures;
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
    int next_id = 0;

    std::map<int, std::string> entity_ids = {};
    std::map<int, Renderable> renderables = {};
    std::map<int, glm::vec3> cameras = {};
    std::map<int, bool> players = {};
    std::map<int, Directional> directionals = {};
    std::map<int, BoundingBox> boundingBoxes = {};
    std::map<int, Movement> movements = {};
    // std::map<int, AnimationCycle> animationCycle = {};

public:
    Entity_Manager() { }

    //// Entity ////
    int createEntity(std::string name = "") {
        entity_ids.emplace(next_id, name);
        return next_id++;
    }

    std::string getEntity(int id) {
        return entity_ids[id];
    }

    //TODO: delete and reuse deleted id's

    //// Square ////
    void setRenderable(int id, glm::vec2 pos, float height, std::vector<unsigned int> textures, glm::vec2 scale = glm::vec2(1.0f, 1.0f)) {
        Renderable square = {pos, scale, height, textures, 0};
        renderables.emplace(id, square);
    }

    Renderable &getRenderable(int id) {
        return renderables[id];
    }

    std::map<int, Renderable> &getRenderables() {
        return renderables;
    }

    //// Cameras ////
    void setCamera(int id, glm::vec3 pos){
        cameras.emplace(id, pos);
    }

    glm::vec3 &getCamera(int id) {
        return cameras[id];
    }

    glm::mat4 getCameraView(int id) {
        glm::vec3 cameraPos = this->getCamera(id);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

    //// Player ////
    void setPlayer(int id, bool active) {
        players.emplace(id, active);
    }

    bool &getPlayer(int id) {
        return players[id];
    }

    //// Directions ////
    void setDirectional(int id, std::vector<unsigned int> south_textures, std::vector<unsigned int> west_textures, std::vector<unsigned int> east_textures, std::vector<unsigned int> north_textures, int direction) {
        Directional dir = {south_textures, west_textures, east_textures, north_textures, direction};
        directionals.emplace(id, dir);
    }

    Directional &getDirectional(int id) {
        return directionals[id];
    }

    std::map<int, Directional> &getDirectionals() {
        return directionals;
    }

    void setDirection(int id, int direction) {
        directionals[id].direction = direction;
    }

    //// Bounding Boxes ////
    void setBoundingBox(int id, float xmin, float xmax, float ymin, float ymax) {
        BoundingBox box = {xmin, xmax, ymin, ymax};
        boundingBoxes.emplace(id, box);
    }

    BoundingBox &getBoundingBox(int id) {
        return boundingBoxes[id];
    }

    std::map<int, BoundingBox> &getBoundingBoxes() {
        return boundingBoxes;
    }

    //// Movement ////
    void setMovement(int id, glm::vec2 velocity, float weight = 50.0f, float friction = 1.0f) {
        Movement tmp = {velocity, weight, friction};
        movements.emplace(id, tmp);
    }

    Movement &getMovement(int id) {
        return movements[id];
    }

    std::map<int, Movement> &getMovements() {
        return movements;
    }

    //// Animation Cycle ////
    // void setAnimationCycle(int id, int cycle_length, int cycle_index) {
    //     AnimationCycle cycle = {cycle_length, cycle_index};
    //     animationCycle.emplace(id, cycle);
    // }

    // std::map<int, AnimationCycle> &getAnimationCycles() {
    //     return animationCycle;
    // }
};

#endif
