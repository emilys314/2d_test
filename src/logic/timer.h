#ifndef TIMER_H
#define TIMER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <queue>

class Timer {
private:
    float time_current = 0.0f;
    float time_delta = 0.0f; // Time between current frame and last frame
    float time_last = 0.0f; // Time of last frame

public:
    Timer() {
        setTime();
    }

    void setTime() {
        time_current = glfwGetTime();
        time_delta = time_current - time_last;
        time_last = time_current;
    }

    float getDeltaTime() {
        return time_delta;
    }

    float getTime() {
        return time_current;
    }
};

#endif
