#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(const glm::vec3* Vertices, const unsigned int& NumVertices);

    void Draw();
private:
    unsigned int VertexArrayObject;
    unsigned int VertexBufferObject;

    unsigned int DrawCount;
};

#endif // MESH_H
