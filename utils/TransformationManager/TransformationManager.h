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
    static constexpr unsigned int orthographic  = 4;
    static constexpr unsigned int perspective  = 5;
    float getTranslationSensitivity() const;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    void moveObject(unsigned int direction);
    void changeProjectionMatrix(unsigned int mode,  int width, int hight);
    explicit TransformationManager(float translationSensitivity);

};


#endif //OPENGLSETUPFROMGLFW_TRANSFORMATIONMANAGER_H
