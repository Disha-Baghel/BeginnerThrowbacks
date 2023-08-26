#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

class Vertex
{
public:
    Vertex(const glm::vec3& pos,const glm::vec2& texCoord)
    {
        this->pos = pos;
        this->texCoord = texCoord;
    }

    glm::vec3& getPos() { return pos;}
    glm::vec2& getTexCoord() { return texCoord;}
private:
    glm::vec3 pos;
    glm::vec2 texCoord;
};

class Mesh
{
public:
    Mesh(Vertex* vertices, unsigned int numVertices);

    void Draw();

    virtual ~Mesh();
protected:
private:
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;

    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        INSTANCE_VB,

        NUM_BUFFERS
    };

    unsigned int m_VertexArrayObject;
    unsigned int m_VertexBufferObject[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif // MESH_H
