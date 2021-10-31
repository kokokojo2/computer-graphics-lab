#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef OPENGLSETUPFROMGLFW_SHADERPROGRAM_H
#define OPENGLSETUPFROMGLFW_SHADERPROGRAM_H


class ShaderProgram {
    unsigned int vertexShaderId{};
public:
    unsigned int getVertexShaderId() const;

    unsigned int getFragmentShaderId() const;

private:
    unsigned int fragmentShaderId{};
    unsigned int id{};
public:
    unsigned int getId() const;

private:
    char infoLog[512];
public:
    ShaderProgram();
    bool addFromSourceString(const char *shader, const int shaderType);
    bool addFromFile(const std::string& fileName, const int shaderType);
    bool make(bool deleteShaders);
    void passUniform4Matrix(const std::string& variableName, glm::mat4 matrix);
    void activate() const;
    char* getInfoLog();
};


#endif
