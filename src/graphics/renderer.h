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

        glEnable(GL_DEPTH_TEST);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void render(Window &window, int camera_id, Entity_Manager &entity_manager) {  
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float scale = 4.0f;     // biger number means zoomed in

        shader_basic.use();
        for (auto const& [id, model] : entity_manager.getSquares()) {
            // bind Texture
            glBindTexture(GL_TEXTURE_2D, model.texture);

            // model
            glm::mat4 mat_model = glm::translate(glm::mat4(1.0f), glm::vec3(model.position, model.height));
            mat_model = glm::scale(mat_model, glm::vec3(model.scale, 1.0f));
            glm::mat4 mat_view = glm::translate(entity_manager.getCameraView(camera_id), glm::vec3(window.getFrameWidth() / (scale*2), window.getFrameHeight() / (scale*2), -1.0f));
            glm::mat4 mat_projection = glm::ortho(0.0f, (float)window.getFrameWidth() / scale, 0.0f, window.getFrameHeight() / scale, 0.1f, 100.0f);
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
