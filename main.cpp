#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <functional>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/ShaderProgram/ShaderProgram.h"
#include "utils/VertexArrayObjectManager/VertexArrayObjectManager.h"
#include "utils/TransformationManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, TransformationManager* transformationManager);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HIGHT = 800;
const std::string VERTEX_SHADER_PATH = "..\\shaders\\vertex.glsl";
const std::string FRAGMENT_SHADER_PATH = "..\\shaders\\frag.glsl";

float vertices[] = {
        -0.8f, 0.36f, 0.0f,
        -0.8f, 0.05f, 0.0f,
        -0.8f, -0.18f, 0.0f,
        -0.63f, 0.18f, 0.0f,
       -0.54f, 0.26f, 0.0f,
        -0.54f, 0.05f, 0.0f,
        -0.54f, -0.08f, 0.0f,
        -0.54f, -0.18f, 0.0f,
        -0.54f, -0.52f, 0.0f,
        -0.29f, -0.3f, 0.0f,
        -0.04f, -0.08f, 0.0f,
        0.22f, -0.3f, 0.0f,
        0.48f, -0.08f, 0.0f,
        0.48f, -0.52f, 0.0f,
        0.54f, 0.15f, 0.0f,
        0.86f, 0.3f, 0.0f,
        0.79f, 0.08f, 0.0f
};

unsigned int indices[] = {
        0, 1, 3,
        1, 4, 5,
        1, 2, 5,
        2, 5, 7,
        6, 8, 10,
        9, 10, 11,
        10, 12, 13,
        12, 14, 15,
        12, 15, 16
};

unsigned int vertexBufferObjConfiguration() {
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return vertexBufferObject;
}

unsigned int elementBufferObjConfiguration() {
    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    return elementBufferObject;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Lab1", nullptr, nullptr);

    glfwMakeContextCurrent(mainWindow);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, SCREEN_HIGHT, SCREEN_WIDTH);
    auto* shaderProgram = new ShaderProgram();
    bool success = shaderProgram->addFromFile(VERTEX_SHADER_PATH, GL_VERTEX_SHADER);
    if(!success) {
        std::cout << "Error while compiling vertex shader.\nDetails:\n" << shaderProgram->getInfoLog() << std::endl;
    }

    success = shaderProgram->addFromFile(FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER);
    if(!success) {
        std::cout << "Error while compiling fragment shader.\nDetails:\n" << shaderProgram->getInfoLog() << std::endl;
    }

    success = shaderProgram->make(false);
    if (!success) {
        std::cout << "Error while linking shaders.\nDetails:\n" << shaderProgram->getInfoLog() << std::endl;
    }

    auto* vertexArrayObj = new VertexArrayObjectManager();

    vertexArrayObj->configureVBOObject(vertexBufferObjConfiguration);
    vertexArrayObj->configureEBOObject(elementBufferObjConfiguration);

    auto* transformationManager = new TransformationManager(0.001);


    while (!glfwWindowShouldClose(mainWindow)) {
        processInput(mainWindow, transformationManager);
        shaderProgram->passUniform4Matrix("transform", transformationManager->getTransformationMatrix());

        glClearColor(0.96f, 0.5f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram->activate();
        vertexArrayObj->bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, TransformationManager* transformationManager) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
        transformationManager->moveObject(TransformationManager::up);
    }
    if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
        transformationManager->moveObject(TransformationManager::down);
    }
    if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
        transformationManager->moveObject(TransformationManager::right);
    }
    if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
        transformationManager->moveObject(TransformationManager::left);
    }
}