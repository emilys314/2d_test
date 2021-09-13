#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



class Window {
private:
    int current_width = 800;
    int current_height = 600;
    
    GLFWwindow * glfwwindow;

public:
    Window() {
        glfwInit();
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
        #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        //// glfw window creation ////
        this->glfwwindow = glfwCreateWindow(current_width, current_height, "LearnOpenGL", NULL, NULL);
        if (this->glfwwindow == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(this->glfwwindow);
        
        //// glad: load all OpenGL function pointers ////
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
        }
        
        glfwSetWindowUserPointer(glfwwindow, static_cast<void *>(this));
        glfwSetFramebufferSizeCallback(this->glfwwindow, [](GLFWwindow *window, int width, int height) {
                        auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
                        glViewport(0, 0, width, height);
            });

        glfwSetWindowUserPointer(glfwwindow, static_cast<void *>(this));
        glfwSetKeyCallback(this->glfwwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                        auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
                        std::cout << "Key " << glfwGetKeyName(key, 0) << " " << action << "\n";
            });

        //// get version info ////
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
    }

    GLFWwindow * getGlfwWindow() {
        return this->glfwwindow;
    }

    bool shouldClose() {
        return (glfwWindowShouldClose(this->glfwwindow));
    }

    void swapBuffers() {
        glfwSwapBuffers(this->glfwwindow);

    }

    void getFramebufferSize(int* width, int* height) {
        glfwGetFramebufferSize(this->glfwwindow, width, height);
    }

    int getFrameWidth() {
        int width, height;
        glfwGetFramebufferSize(this->glfwwindow, &width, &height);
        return width;
    }

    int getFrameHeight() {
        int width, height;
        glfwGetFramebufferSize(this->glfwwindow, &width, &height);
        return height;
    }
};

#endif