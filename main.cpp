#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <functional>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils/ShaderProgram/ShaderProgram.h"
#include "utils/VertexArrayObjectManager/VertexArrayObjectManager.h"
#include "utils/TransformationManager/TransformationManager.h"
#include "utils/CameraManager/CameraManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, TransformationManager* transformationManager,  CameraManager* cameraManager);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HIGHT = 1200;
const std::string VERTEX_SHADER_PATH = "..\\shaders\\vertex.glsl";
const std::string FRAGMENT_SHADER_PATH = "..\\shaders\\frag.glsl";

bool firstMouse = true;
glm::vec2 lastMousePos = glm::vec2(SCREEN_HIGHT / 2.0f, SCREEN_HIGHT / 2.0f);

auto* cameraManager = new CameraManager(
        glm::vec3(0.0f, 2.0f, 10.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f,  0.0f),
        0.005,
        0.1
);

float cubeVertices [] = {
        -0.5, -0.5, 0.5, // 0
        0.5, -0.5, 0.5, // 1
        0.5, 0.5, 0.5, // 2
        -0.5, 0.5, 0.5, // 3
        -0.5, -0.5, -0.5, // 4
        0.5, -0.5, -0.5, // 5
        0.5, 0.5, -0.5, // 6
        -0.5, 0.5, -0.5 // 7
};

unsigned int cubeIndices[] = {
        // front
        0, 1, 2,
        0, 2, 3,
        // right
        1, 5, 6,
        1, 2, 6,
        // left
        0, 4, 7,
        0, 3, 7,
        // back
        4, 5, 7,
        5, 6, 7,
        // top
        2, 3, 6,
        3, 6, 7,
        // bottom
        0, 1, 5,
        0, 4, 5
};


unsigned int CubeVertexBufferObjConfiguration() {
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return vertexBufferObject;
}

unsigned int CubeElementBufferObjConfiguration() {
    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    return elementBufferObject;
}

float dodecahedronVertices[] = {
        1, 1, 1, // 0
        1, 1, -1, // 1
        1, -1, 1, // 2
        1, -1, -1, // 3
        -1, 1, 1, // 4
        -1, 1, -1, // 5
        -1, -1, 1, // 6
        -1, -1, -1, // 7
        0, 0.618, 1.618, // 8
        0, 0.618, -1.618, // 9
        0, -0.618, 1.618, // 10
        0, -0.618, -1.618, // 11
        0.618, 1.618, 0, // 12
        0.618, -1.618, 0, // 13
        -0.618, 1.618, 0, // 14
        -0.618, -1.618, 0, // 15
        1.618, 0, 0.618, // 16
        1.618, 0, -0.618, // 17
        -1.618, 0, 0.618, // 18
        -1.618, 0, -0.618 // 19

        };

unsigned int dodecahedronIndices[] = {
        0, 16, 2,
        2, 10, 8,
        2, 0, 8,

        0, 8, 4,
        4, 14, 12,
        4, 0, 12,

        16, 17, 1,
        1, 12, 0,
        1, 16, 0,

        1, 9, 11,
        11, 3, 17,
        11, 1, 17,

        1, 12, 14,
        14, 5, 9,
        14, 1, 9,

        2, 13, 15,
        15, 6, 10,
        15, 2, 10,

        13, 3, 17,
        17, 16, 2,
        17, 13, 2,

        3, 11, 7,
        7, 15, 13,
        7, 3, 13,

        4, 8, 10,
        10, 6, 18,
        10, 4, 18,

        14, 5, 19,
        19, 18, 4,
        19, 14, 4,

        5, 19, 7,
        7, 11, 9,
        7, 5, 9,

        15, 7, 19,
        19, 18, 6,
        19, 15, 6
};

unsigned int DodecahedronVertexBufferObjConfiguration() {
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(dodecahedronVertices), dodecahedronVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return vertexBufferObject;
}


unsigned int DodecahedronElementBufferObjConfiguration() {
    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dodecahedronIndices), dodecahedronIndices, GL_STATIC_DRAW);

    return elementBufferObject;
}

float floorVertices[] {
    50, 0, 50,
    -50, 0 ,50,
    50, 0 , -50,
    -50, 0, -50
};

unsigned int floorIndices[] {
    0, 1, 2,
    1, 2, 3
};

unsigned int FloorVertexBufferObjConfiguration() {
    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return vertexBufferObject;
}


unsigned int FloorElementBufferObjConfiguration() {
    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);

    return elementBufferObject;
}

void configureSpaceMatrices(TransformationManager* transformationManager) {
    transformationManager->view  = glm::translate(
            transformationManager->view,
            glm::vec3(0.0f, 0.0f, -3.0f)
            );

    transformationManager->projection = glm::perspective(
            glm::radians(45.0f),
            (float)SCREEN_WIDTH / (float)SCREEN_HIGHT,
            0.1f, 100.0f
            );
}

float f(float x, float z) {
    return sqrt(x) + sqrt(z);
}

void getGraphVerticesArray(float *vertices, int start, int stop, float step) {
    int index = 0;
    for (float i = start; i < stop; i += step) {
        vertices[index] = i; // x
        index++;
        vertices[index] = f(i, 0); // y
        index++;
        vertices[index] = 0; // z
        index++;
    }
}

unsigned int GraphVertexBufferObjConfiguration() {
    int start = 0, stop = 5;
    float step = 0.5;
    int size = ((stop - start) / step ) * 3;

    float graphIndexArr [size];
    getGraphVerticesArray(graphIndexArr, 0, 5, 0.5);

    for (int i = 0; i < size; i++) {
        std::cout << graphIndexArr[i] << " ";
    }

    unsigned int vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(graphIndexArr), graphIndexArr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    return vertexBufferObject;
}

int main() {
    int start = 0, stop = 5;
    float step = 0.5;
    int size = ((stop - start) / step ) * 3;

    float graphIndexArr [size];
    getGraphVerticesArray(graphIndexArr, 0, 5, 0.5);

    for (int i = 0; i < size; i++) {
        std::cout << graphIndexArr[i] << " ";
    }

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* mainWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Lab1", nullptr, nullptr);

    glfwMakeContextCurrent(mainWindow);
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mainWindow, mouse_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    auto* CubeVertexArrayObj = new VertexArrayObjectManager();
    CubeVertexArrayObj->configureVBOObject(CubeVertexBufferObjConfiguration);
    CubeVertexArrayObj->configureEBOObject(CubeElementBufferObjConfiguration);

    auto* DodecahedronVertexArrayObj = new VertexArrayObjectManager();
    DodecahedronVertexArrayObj->configureVBOObject(DodecahedronVertexBufferObjConfiguration);
    DodecahedronVertexArrayObj->configureEBOObject(DodecahedronElementBufferObjConfiguration);

    auto* FloorVertexArrayObj = new VertexArrayObjectManager();
    FloorVertexArrayObj->configureVBOObject(FloorVertexBufferObjConfiguration);
    FloorVertexArrayObj->configureEBOObject(FloorElementBufferObjConfiguration);

    auto* GraphVertexArrayObj = new VertexArrayObjectManager();
    GraphVertexArrayObj->configureVBOObject(GraphVertexBufferObjConfiguration);

    auto* transformationManager = new TransformationManager(0.001);

    configureSpaceMatrices(transformationManager);

    while (!glfwWindowShouldClose(mainWindow)) {
        processInput(mainWindow, transformationManager, cameraManager);
        shaderProgram->passUniform4Matrix("model", transformationManager->model);
        shaderProgram->passUniform4Matrix("view", cameraManager->getLookAtMatrix());
        shaderProgram->passUniform4Matrix("projection", transformationManager->projection);

        glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram->activate();


        transformationManager->model = glm::translate(
                transformationManager->model,
                glm::vec3( 5.0f,  0.0f,  0.0f)
                );

        shaderProgram->passUniform4Matrix("model", transformationManager->model);
        shaderProgram->passUniform4Vec("color", glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
        CubeVertexArrayObj->bind();
        glDrawElements(GL_TRIANGLES, sizeof(cubeIndices), GL_UNSIGNED_INT, nullptr);
        CubeVertexArrayObj->unbind();


        transformationManager->model = glm::translate(
                glm::mat4(1.0f),
                glm::vec3( -5.0f,  0.0f,  0.0f)
        );
        shaderProgram->passUniform4Matrix("model", transformationManager->model);
        shaderProgram->passUniform4Vec("color", glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));

        DodecahedronVertexArrayObj->bind();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glDrawElements(GL_TRIANGLES, sizeof(dodecahedronIndices), GL_UNSIGNED_INT, nullptr);
        DodecahedronVertexArrayObj->unbind();


        transformationManager->model = glm::translate(
                glm::mat4(1.0f),
                glm::vec3( 0.0f,  -2.0f,  0.0f)
        );
        shaderProgram->passUniform4Matrix("model", transformationManager->model);
        shaderProgram->passUniform4Vec("color", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        FloorVertexArrayObj->bind();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, sizeof(floorIndices), GL_UNSIGNED_INT, nullptr);
        FloorVertexArrayObj->unbind();

        transformationManager->model = glm::translate(
                glm::mat4(1.0f),
                glm::vec3( 0.0f,  1.0f,  0.0f)
        );
        shaderProgram->passUniform4Matrix("model", transformationManager->model);
        shaderProgram->passUniform4Vec("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

        GraphVertexArrayObj->bind();
        glDrawArrays(GL_LINE_STRIP, 0, 10); // TODO: hardcoded
        GraphVertexArrayObj->unbind();
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, TransformationManager* transformationManager, CameraManager* cameraManager) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
        cameraManager->moveCamera(CameraManager::front);
    }
    if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
        cameraManager->moveCamera(CameraManager::back);
    }
    if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
        cameraManager->moveCamera(CameraManager::right);

    }
    if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
        cameraManager->moveCamera(CameraManager::left);
    }

    if (glfwGetKey(window,GLFW_KEY_P) == GLFW_PRESS) {
        transformationManager->changeProjectionMatrix(TransformationManager::perspective, SCREEN_WIDTH, SCREEN_HIGHT);
    }

    if (glfwGetKey(window,GLFW_KEY_O) == GLFW_PRESS) {
        transformationManager->changeProjectionMatrix(TransformationManager::orthographic, SCREEN_WIDTH, SCREEN_HIGHT);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastMousePos.x = xpos;
        lastMousePos.y = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastMousePos.x;
    float yOffset = lastMousePos.y - ypos; // reversed since y-coordinates go from bottom to top

    lastMousePos.x = xpos;
    lastMousePos.y = ypos;

    std::cout << xOffset << " " << yOffset << std::endl;
    cameraManager->changeCameraDirection(xOffset, yOffset);
}