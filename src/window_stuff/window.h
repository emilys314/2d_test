#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>



class Window {
private:
    int current_width = 800;
    int current_height = 600;

    double lastTime = glfwGetTime();
    int frame_count = 0;

public:
    GLFWwindow* glfwwindow;

    Window() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            printf("Failed to initialize OpenGL context\n");
        }

        glfwSetWindowUserPointer(glfwwindow, static_cast<void*>(this));
        glfwSetFramebufferSizeCallback(this->glfwwindow, [](GLFWwindow* window, int width, int height) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            std::cout << width << " " << height << "\n";
            glViewport(0, 0, width, height);
            });

        glfwSetWindowUserPointer(glfwwindow, static_cast<void*>(this));
        glfwSetKeyCallback(this->glfwwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            std::cout << "Key " << glfwGetKeyName(key, 0) << " " << action << "\n";
            });

        //// get version info ////
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
        printf("Loaded GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    }

    void performance_counter() {
        double currentTime = glfwGetTime();
        frame_count++;
        if (currentTime - lastTime >= 1.0) { // If last printf() was more than 1 sec ago
            std::string title = std::to_string(frame_count) + "fps";
            glfwSetWindowTitle(this->getGlfwWindow(), title.c_str());

            frame_count = 0;
            lastTime = currentTime;
        }
    }

    GLFWwindow* getGlfwWindow() {
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