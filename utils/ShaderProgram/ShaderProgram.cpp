#include "ShaderProgram.h"
#include<fstream>
#include<sstream>
#include <glad/glad.h>

ShaderProgram::ShaderProgram() {

}

bool ShaderProgram::addFromSourceString(const char *shader, const int shaderType) {
        unsigned int shaderId = glCreateShader(shaderType);

        glShaderSource(shaderId, 1, &shader, nullptr);
        glCompileShader(shaderId);

        int success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
        }

        if (shaderType == GL_VERTEX_SHADER) vertexShaderId = shaderId;
        else if (shaderType == GL_FRAGMENT_SHADER) fragmentShaderId = shaderId;

        return success;
}

bool ShaderProgram::addFromFile(const std::string& fileName, const int shaderType) {
    std::ifstream file(fileName);
    std::string fileContents;

    if(file) {
        std::ostringstream buffer;
        buffer << file.rdbuf();
        fileContents = buffer.str();
    } else {
        std::cout << "File error.\n";
        return false;
    }

    const char *tempFileContents = fileContents.c_str();
    return this->addFromSourceString(tempFileContents, shaderType);
}

bool ShaderProgram::make(bool deleteShaders) {
    id = glCreateProgram();

    glAttachShader(id, vertexShaderId);
    glAttachShader(id, fragmentShaderId);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
    }

    if (deleteShaders) {
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    return success;
}

void ShaderProgram::activate() const {
    glUseProgram(id);
}

char* ShaderProgram::getInfoLog() {
    return infoLog;
}

unsigned int ShaderProgram::getVertexShaderId() const {
    return vertexShaderId;
}

unsigned int ShaderProgram::getFragmentShaderId() const {
    return fragmentShaderId;
}

unsigned int ShaderProgram::getId() const {
    return id;
}

void ShaderProgram::passUniform4Matrix(const std::string &variableName, glm::mat4 matrix) {
    unsigned int transformLoc = glGetUniformLocation(this->getId(), variableName.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}
