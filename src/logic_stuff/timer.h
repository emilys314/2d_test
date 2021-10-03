#ifndef TIMER_H
#define TIMER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Timer {
private:
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    bool full_second = false;
    float next_full = 0.0f;

    bool half_second = false;
    float next_half = 0.0f;

    bool quarter_second = false;
    float next_quarter = 0.0f;

public:
    Timer() {
        setTime();
        next_full = trunc(lastFrame) + 1.00f;
        next_half = trunc(lastFrame) + 1.50f;
        next_full = trunc(lastFrame) + 1.25f;
    }

    void setTime() {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        full_second = false;
        half_second = false;
        quarter_second = false;
        if (currentFrame > next_full) {
            full_second = true;
            next_full += 1.0f;
            std::cout << "full\n";
        }
        if (currentFrame > next_half) {
            half_second = true;
            next_half += 0.5f;
            std::cout << "half\n";
        }
        if (currentFrame > next_quarter) {
            quarter_second = true;
            next_quarter += 0.25f;
            std::cout << "quarter\n";
        }
    }
    
    float getDeltaTime() {
        return deltaTime;
    }

    float getTime() {
        return glfwGetTime();
    }

    bool getFullSecond() {
        return full_second;
    }

    bool getHalfSecond() {
        return half_second;
    }

    bool getQuarterSecond() {
        return quarter_second;
    }
};

#endif
