#include <iostream>
#include <functional>

#ifndef OPENGLSETUPFROMGLFW_VERTEXARRAYOBJECTMANAGER_H
#define OPENGLSETUPFROMGLFW_VERTEXARRAYOBJECTMANAGER_H


class VertexArrayObjectManager {
    unsigned int objectId{};
    unsigned int vertexBufferId{};
    unsigned int elementBufferId{};

public:
    unsigned int getObjectId() const;
    unsigned int getVBOid() const;
    unsigned int getEBOid() const;
    void bind();
    void unbind();
    VertexArrayObjectManager();
    void configureVBOObject(const std::function<unsigned int()>& configurationProcedure);
    void configureEBOObject(const std::function<unsigned int()>& configurationProcedure);
};


#endif
