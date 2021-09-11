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
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    unsigned int texture;
};

class Entity_Manager {
private:
    std::map<int, std::string> entity_ids = {};
    int next_id = 0;

    std::map<int, Square> squares = {};

    std::map<int, glm::vec3> cameras = {};

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
    void setSquare(int id, glm::vec3 pos, unsigned int tex) {
        Square square = {pos, tex};
        squares.emplace(id, square);
    }

    Square getSquare(int id) {
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

};

#endif
