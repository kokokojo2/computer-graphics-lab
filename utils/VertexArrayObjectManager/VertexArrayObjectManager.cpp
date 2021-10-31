#include "VertexArrayObjectManager.h"
#include <glad/glad.h>

unsigned int VertexArrayObjectManager::getObjectId () const {
    return objectId;
}

unsigned int VertexArrayObjectManager::getVBOid () const {
    return vertexBufferId;
}

unsigned int VertexArrayObjectManager::getEBOid () const {
    return elementBufferId;
}

void VertexArrayObjectManager::bind() {
    glBindVertexArray(objectId);
}

void VertexArrayObjectManager::unbind() {
    glBindVertexArray(0);
}

VertexArrayObjectManager::VertexArrayObjectManager() {
    glGenVertexArrays(1, &objectId);
}

void VertexArrayObjectManager::configureVBOObject(const std::function<unsigned int()>& configurationProcedure) {
    this->bind();
    vertexBufferId = configurationProcedure();
    this->unbind();
}

void VertexArrayObjectManager::configureEBOObject(const std::function<unsigned int()>& configurationProcedure) {
    this->bind();
    elementBufferId = configurationProcedure();
    this->unbind();
}
