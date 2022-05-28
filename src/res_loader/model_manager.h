#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <map>
#include <string>

#include <glad/gl.h>

#include "../graphics/model.h"

float flat_square_vertices[] = {
    // positions      // tex coords
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
};
unsigned int flat_sqaure_indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

class Model_Manager {
    std::map<std::string, Model> models = {};

public:
    Model_Manager() {
        Model temp_model = {};

        glGenVertexArrays(1, &temp_model.VAO);
        glGenBuffers(1, &temp_model.VBO);
        glGenBuffers(1, &temp_model.EBO);

        glBindVertexArray(temp_model.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, temp_model.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(flat_square_vertices), flat_square_vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, temp_model.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(flat_sqaure_indices), flat_sqaure_indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        temp_model.index_count = 6;

        models["flat_square"] = temp_model;
    }

    Model get(std::string file_path) {
        if (file_path == "flat_square")
            return models["flat_square"];
        // if (file_path == "angled_square")
        //     return 
        else {
            std::cerr << "Invalid model file_path supplied: " << file_path << "\n";
            return models["flat_square"];
        }
    }
};

#endif