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

#include "../graphics/texture.h"

struct Entity {
    std::string name = "";
    // int parent = 0;
    // std::vector<int> children;
};

struct Renderable {
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    glm::vec2 scale = glm::vec2(1.0f, 1.0f);
    float height;
    // unsigned int texture;       //texture id
    std::vector<Texture> textures;
    int texture_index = 0;
    int parent = 0;
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

public:
    std::map<int, Entity> entity_ids = {};
    std::map<int, Renderable> renderables = {};
    std::map<int, glm::vec3> cameras = {};
    std::map<int, bool> players = {};
    std::map<int, Directional> directionals = {};
    std::map<int, BoundingBox> boundingBoxes = {};
    std::map<int, Movement> movements = {};

    Entity_Manager() { }

    //// Entity ////
    int createEntity(std::string name = "") {
        Entity entity = {name};
        entity_ids.emplace(next_id, entity);
        return next_id++;
    }

    Entity getEntity(int id) {
        return entity_ids[id];
    }

    //TODO: delete and reuse deleted id's

    //// Square ////
    Renderable setRenderable(int id, glm::vec2 pos, float height, std::vector<Texture> textures) {
        glm::vec2 scale = glm::vec2(textures[0].getWidth(), textures[0].getHeight());
        Renderable square = {pos, scale, height, textures, 0, 0};
        renderables.emplace(id, square);
        return square;
    }

    Renderable &getRenderable(int id) {
        return renderables[id];
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
    void setDirectional(int id, std::vector<Texture> south_textures, std::vector<Texture> west_textures, std::vector<Texture> east_textures, std::vector<Texture> north_textures, int direction) {
        Directional dir = {south_textures, west_textures, east_textures, north_textures, direction};
        directionals.emplace(id, dir);
    }

    Directional &getDirectional(int id) {
        return directionals[id];
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

    //// Movement ////
    void setMovement(int id, glm::vec2 velocity, float weight = 50.0f, float friction = 1.0f) {
        Movement tmp = {velocity, weight, friction};
        movements.emplace(id, tmp);
    }

    Movement &getMovement(int id) {
        return movements[id];
    }
};

#endif
