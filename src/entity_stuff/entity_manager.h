#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Square {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    unsigned int texture;
};

class Entity_Manager {
private:
    std::map<int, std::string> entity_ids = {};
    int next_id = 0;

    std::map<int, Square> squares = {};

public:
    Entity_Manager() { }

    int createEntity(std::string name = "") {
        entity_ids.emplace(next_id, name);
        return next_id++;
    }

    std::string getEntity(int id) {
        return entity_ids[id];
    }

    //TODO delete and reuse deleted id's

    void setModel(int id, glm::vec3 pos, unsigned int tex) {
        Square square = {pos, tex};
        squares.emplace(id, square);
    }

    Square getModel(int id) {
        return squares[id];
    }

    std::map<int, Square> &getSquares() {
        return squares;
    }
};

#endif
