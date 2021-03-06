#include <glm/mat4x4.hpp>
#include <iostream>

#ifndef OPENGLSETUPFROMGLFW_TRANSFORMATIONMANAGER_H
#define OPENGLSETUPFROMGLFW_TRANSFORMATIONMANAGER_H


class TransformationManager {
    float translationSensitivity{};
    glm::mat4 transformationMatrix;
public:
    const glm::mat4 &getTransformationMatrix() const;
    static constexpr unsigned int right = 0;
    static constexpr unsigned int left = 1;
    static constexpr unsigned int up = 2;
    static constexpr unsigned int down = 3;
    float getTranslationSensitivity() const;
    void moveObject(unsigned int direction);
    explicit TransformationManager(float translationSensitivity);

};


#endif //OPENGLSETUPFROMGLFW_TRANSFORMATIONMANAGER_H
