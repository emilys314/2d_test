#ifndef TIMER_H
#define TIMER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <queue>

struct Event {
    int eventid;
    float timestamp;
    bool ready;
};

class Timer {
private:
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    std::queue<float> events = {};

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

    float getTime() {
        return glfwGetTime();
    }
};

#endif
