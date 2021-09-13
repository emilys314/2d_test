#ifndef TIMER_H
#define TIMER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Timer {
private:
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

public:
    Timer() {
        setTime();
    }

    void setTime() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
    
    float getDeltaTime() {
        return deltaTime;
    }
};

#endif
