#ifndef MODEL_H
#define MODEL_H


struct Model {
    unsigned int VBO;       // Vertex Buffer Object
    unsigned int VAO;       // Vertex Array Object
    unsigned int EBO;       // Element Buffer Object
    int index_count;
    int usage_count;        // Number of entities using this model. Delete when 0
};

#endif