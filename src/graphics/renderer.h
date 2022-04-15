#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "../res_loader/model_square.h"
#include "../res_loader/texture_loader.h"
#include "../entity_management/entity_manager.h"
#include "../window_stuff/window.h"


class Renderer {
private:
    GLFWwindow *glfwwindow;
    Shader shader;
    Model_Square square;

public:
    Renderer() {}

    Renderer(Window &window) {
        // build and compile our shader program
        shader = Shader("src/graphics/basic.vs", "src/graphics/basic.fs");

        // load model(s)
        square = Model_Square();

        glEnable(GL_DEPTH_TEST);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void render(Window &window, int camera_id, Entity_Manager &entity_manager) {  
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float scale = 4.0f;     // bigger number means zoomed in

        shader.use();
        for (auto& [id, model] : entity_manager.renderables) {
            // bind Texture
            glBindTexture(GL_TEXTURE_2D, model.textures[model.texture_index].getId());

            glm::vec2 parent_pos = glm::vec2(0.0f, 0.0f);
            if (model.parent > 0) {
                parent_pos = entity_manager.renderables[model.parent].position;
                printf("%f %f", parent_pos.x, parent_pos.y);
            }
            // printf("%f %f", parent_pos.x, parent_pos.y);

            // model
            glm::mat4 mat_model = glm::translate(glm::mat4(1.0f), glm::vec3(model.position + parent_pos, model.height));
            mat_model = glm::scale(mat_model, glm::vec3(model.scale, 1.0f));
            glm::mat4 mat_view = glm::translate(entity_manager.getCameraView(camera_id), glm::vec3(window.getFrameWidth() / (scale*2), window.getFrameHeight() / (scale*2), 0.0f));
            glm::mat4 mat_projection = glm::ortho(0.0f, (float)window.getFrameWidth() / scale, 0.0f, window.getFrameHeight() / scale, 0.1f, 100.0f);

            glm::mat4 mat_mvp = mat_projection * mat_view * mat_model;

            shader.setMat4("uni_mvp", mat_mvp);

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