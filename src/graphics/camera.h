#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);

public:
    glm::vec3 getPosition() {
        return cameraPos;
    }

    void setPosition(glm::vec3 newPos) {
        cameraPos = newPos;
    }

    glm::mat4 getView() {
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
};

#endif
