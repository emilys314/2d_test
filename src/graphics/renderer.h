#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "../res_loader/model_square.h"
#include "../res_loader/texture_loader.h"
#include "../entity_stuff/entity_manager.h"
#include "../window_stuff/window.h"


class Renderer {
private:
    GLFWwindow *glfwwindow;
    Shader shader_basic;
    Model_Square square;
    unsigned int texture;

public:
    Renderer() {}
    
    Renderer(Window &window) {
        // build and compile our shader zprogram
        shader_basic = Shader("src/graphics/shader.vs", "src/graphics/shader.fs");

        // load model(s)
        square = Model_Square();
    }

    void render(Window &window, Camera &camera, Entity_Manager &entity_manager) {  
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_basic.use();
        for (auto const& [id, model] : entity_manager.getSquares()) {
            // bind Texture
            glBindTexture(GL_TEXTURE_2D, model.texture);

            // model
            glm::mat4 mat_model = glm::translate(glm::mat4(1.0f), model.position);
            glm::mat4 mat_view = camera.getView();
            glm::mat4 mat_projection = glm::ortho(0.0f, window.getFrameWidth() / 100.0f, 0.0f, window.getFrameHeight() / 100.0f, 0.1f, 100.0f);
            glm::mat4 mat_mvp = mat_projection * mat_view * mat_model;
            int uni_mvp = glGetUniformLocation(shader_basic.ID, "uni_mvp");
            glUniformMatrix4fv(uni_mvp, 1, GL_FALSE, glm::value_ptr(mat_mvp));

            // draw
            glBindVertexArray(square.getVAO());
            glDrawElements(GL_TRIANGLES, square.getCount(), GL_UNSIGNED_INT, 0);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.swapBuffers();
        glfwPollEvents();
    }

    
};


#endif
