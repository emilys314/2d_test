#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Inputs {
private:
    int current_width = 800;
    int current_height = 600;

    GLFWwindow *glfwwindow;

    int keys [512] = {};
    int mouse_buttons [8] = {};
    double cursor_x = 0.0;
    double cursor_y = 0.0;

public:
    Inputs(GLFWwindow *glfwwindow) {
        this->glfwwindow = glfwwindow;
        glfwSetWindowUserPointer(glfwwindow, static_cast<void *>(this));
        glfwSetKeyCallback(this->glfwwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                                auto self = static_cast<Inputs *>(glfwGetWindowUserPointer(window));
                                self->keys[key] = action;
                            });

        glfwSetMouseButtonCallback(glfwwindow, [](GLFWwindow* window, int button, int action, int mods) {
                                auto self = static_cast<Inputs *>(glfwGetWindowUserPointer(window));
                                self->mouse_buttons[button] = action;
                            });

        glfwSetCursorPosCallback(glfwwindow, [](GLFWwindow* window, double xpos, double ypos) {
                                auto self = static_cast<Inputs *>(glfwGetWindowUserPointer(window));
                                self->cursor_x = xpos;
                                self->cursor_y = ypos;
                            });
    }

    int getKey(int key) {
        return keys[key];
    }

    int getMouseButton(int button) {
        return mouse_buttons[button];
    }

    double getCursorX() {
        return cursor_x;
    }

    double getCursorY() {
        return cursor_y;
    }

};

#endif