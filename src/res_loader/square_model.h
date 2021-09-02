#ifndef SQUARE_MODEL_H
#define SQUARE_MODEL_H

#include <glad/glad.h>

float vertices[] = {
    // positions      // tex coords
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
};
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

class Square {
private:
    unsigned int VBO;       // Vertex Buffor Object
    unsigned int VAO;       // Vertex Array Object
    unsigned int EBO;       // Element Buffer Object

public:
    Square() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    unsigned int getVAO() {
        return VAO;
    }

    int getCount() {
        return 6;
    }
};

#endif
