#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Inputs {
private:
    int current_width = 800;
    int current_height = 600;

    GLFWwindow *glfwwindow;

    int keys [512] = {};

public:
    Inputs(GLFWwindow *glfwwindow) {
        this->glfwwindow = glfwwindow;

        glfwSetWindowUserPointer(glfwwindow, static_cast<void *>(this));
        glfwSetKeyCallback(this->glfwwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                               auto self = static_cast<Inputs *>(glfwGetWindowUserPointer(window));
                               std::cout << "Key " << glfwGetKeyName(key, 0) << " " << action << "\n";
                               self->keys[key] = action;
                           });
    }

    int getKey(int key) {
        // std::cout << key << " " << keys[key] << "\n";
        return keys[key];
    }

};

#endif