#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "../res_loader/square_model.h"
#include "../res_loader/texture_loader.h"
#include "../window_stuff/window.h"

class Renderer {
private:
    GLFWwindow *glfwwindow;
    Shader ourShader;
    Square square;
    unsigned int texture;

public:
    Renderer(Window &window) {
        // build and compile our shader zprogram
        ourShader = Shader("src/graphics/shader.vs", "src/graphics/shader.fs");

        // load model(s)
        square = Square();
        texture = load_texture_2d("res/wall.jpg");
    }


    void render(Window &window, Inputs &inputs, Camera &camera) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();

        // set up mvp mat4 
        glm::mat4 model = glm::mat4(1.0f);
        int width, height;
        window.getFramebufferSize(&width, &height);
        glm::mat4 projection = glm::ortho(0.0f, width / 100.0f, 0.0f, height / 100.0f, 0.1f, 100.0f);
        glm::mat4 mvp = projection * camera.getView() * model;

        int uni_mvp = glGetUniformLocation(ourShader.ID, "uni_mvp");
        glUniformMatrix4fv(uni_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

        // draw
        glBindVertexArray(square.getVAO());
        glDrawElements(GL_TRIANGLES, square.getCount(), GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        window.swapBuffers();
        glfwPollEvents();
    }

    
};


#endif
