#include "CameraManager.h"
#include "iostream"

glm::mat4 CameraManager::getLookAtMatrix() {
    return glm::lookAt(positionVec, positionVec + frontVec, upVec);
}

void CameraManager::moveCamera(unsigned int direction) {
    switch (direction) {
        case right:
            positionVec += glm::normalize(glm::cross(frontVec, upVec)) * moveSpeed;
            break;
        case left:
            positionVec -= glm::normalize(glm::cross(frontVec, upVec)) * moveSpeed;
            break;
        case front:
            positionVec += moveSpeed * frontVec;
            break;
        case back:
            positionVec -= moveSpeed * frontVec;
            break;
        default:
            break;
    }
}

CameraManager::CameraManager(glm::vec3 position, glm::vec3 front, glm::vec3 up, float moveSpeed, float mouseSens) {
    this->positionVec = position;
    this->frontVec = front;
    this->upVec = up;
    this->moveSpeed = moveSpeed;
    this->worldUp = up;
    this->mouseSensitivity = mouseSens;
}

void CameraManager::changeCameraDirection(float xOffset, float yOffset) {
    xOffset *= this->mouseSensitivity;
    yOffset *= this->mouseSensitivity;

    std::cout << "changed" << std::endl;
    this->yaw += xOffset;
    this->pitch += yOffset;

    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    newFront.y = sin(glm::radians(this->pitch));
    newFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    frontVec = glm::normalize(newFront);

    this->rightVec = glm::normalize(glm::cross(this->frontVec, this->worldUp));
    this->upVec = glm::normalize(glm::cross(this->rightVec, this->frontVec));
}
