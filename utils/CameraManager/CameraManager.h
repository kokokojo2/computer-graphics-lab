#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef OPENGLSETUPFROMGLFW_CAMERAMANAGER_H
#define OPENGLSETUPFROMGLFW_CAMERAMANAGER_H


class CameraManager {
public:
    glm::vec3 positionVec;
    glm::vec3 frontVec;
    glm::vec3 upVec;
    glm::vec3 rightVec;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float moveSpeed;
    float mouseSensitivity;

    static constexpr unsigned int right = 0;
    static constexpr unsigned int left = 1;
    static constexpr unsigned int front = 2;
    static constexpr unsigned int back = 3;

    glm::mat4 getLookAtMatrix();
    void moveCamera(unsigned int direction);
    void changeCameraDirection(float xOffset, float yOffset);
    CameraManager(glm::vec3 position, glm::vec3 front, glm::vec3 up, float moveSpeed, float mouseSens);
};


#endif
