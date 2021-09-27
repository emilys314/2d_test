#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Square {
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    glm::vec2 scale = glm::vec2(1.0f, 1.0f);
    float height;
    unsigned int texture;       //texture id
};

enum Directions {
    SOUTH = 0,
    WEST = 1,
    EAST = 2,
    NORTH = 3
};

struct Directional {
    unsigned int south_texture;
    unsigned int west_texture;
    unsigned int east_texture;
    unsigned int north_texture;
    int direction = SOUTH;
};

struct BoundingBox {
    float xmin, xmax;
    float ymin, ymax;
};

struct CollisionCircle {
    float xoffset, yoffset;
    float radius;
};

class Entity_Manager
{
private:
    int next_id = 0;

    std::map<int, std::string> entity_ids = {};
    std::map<int, Square> squares = {};
    std::map<int, glm::vec3> cameras = {};
    std::map<int, bool> players = {};
    std::map<int, Directional> directionals = {};
    std::map<int, BoundingBox> boundingBoxes = {};
    std::map<int, CollisionCircle> collisionCircles = {};

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

    //TODO delete and reuse deleted id's

    //// Square ////
    void setSquare(int id, glm::vec2 pos, float height, unsigned int tex, glm::vec2 scale = glm::vec2(1.0f, 1.0f)) {
        Square square = {pos, scale, height, tex};
        squares.emplace(id, square);
    }

    Square &getSquare(int id) {
        return squares[id];
    }

    std::map<int, Square> &getSquares() {
        return squares;
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

    void setPlayer(int id, bool active) {
        players.emplace(id, active);
    }

    bool &getPlayer(int id) {
        return players[id];
    }

    //// Directions ////
    void setDirectional(int id, unsigned int south_texture, unsigned int west_texture , unsigned int east_texture, unsigned int north_texture, int direction) {
        Directional dir = {south_texture, west_texture, east_texture, north_texture, direction};
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

    //// Collision Circles ////
    void setCollisionCircle(int id, float xoffset, float yoffset, float radius) {
        CollisionCircle circle = {xoffset, yoffset, radius};
        collisionCircles.emplace(id, circle);
    }

    CollisionCircle &getCollisionCircle(int id) {
        return collisionCircles[id];
    }

    std::map<int, CollisionCircle> &getCollisionCircles() {
        return collisionCircles;
    }
};

#endif
