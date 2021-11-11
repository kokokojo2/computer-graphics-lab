#include "TransformationManager.h"
#include <glm/gtc/matrix_transform.hpp>

float TransformationManager::getTranslationSensitivity() const {
    return translationSensitivity;
}

TransformationManager::TransformationManager(float translationSensitivity) {
    this->translationSensitivity = translationSensitivity;
    this->transformationMatrix = glm::mat4(1.0f);
}

void TransformationManager::moveObject(unsigned int direction) {
    glm::vec3 directionVector;
    switch (direction) {
        case right:
            directionVector = glm::vec3(1.0f * translationSensitivity, 0.0f, 0.0f);
            break;
        case left:
            directionVector = glm::vec3(-1.0f * translationSensitivity, 0.0f, 0.0f);
            break;
        case up:
            directionVector = glm::vec3(0.0f, 1.0f * translationSensitivity, 0.0f);
            break;
        case down:
            directionVector = glm::vec3(0.0f, -1.0f * translationSensitivity, 0.0f);
            break;
        default:
            std::cout << "Unknown direction for construction translation matrix." << std::endl;
            break;
    }

    transformationMatrix = glm::translate(
            transformationMatrix,
            directionVector
    );
}

const glm::mat4 &TransformationManager::getTransformationMatrix() const {
    return transformationMatrix;
}
