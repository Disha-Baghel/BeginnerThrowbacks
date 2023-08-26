#include "Mesh.h"
#include <GL/glew.h>
#include <vector>

std::vector<glm::vec3> translation;

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
    m_drawCount = numVertices;

    glGenVertexArrays(1,&m_VertexArrayObject);
    glBindVertexArray(m_VertexArrayObject);

    std::vector<glm::vec3> Position;
    std::vector<glm::vec2> TexCoord;

    Position.reserve(numVertices);
    TexCoord.reserve(numVertices);

    for(unsigned int i = 0; i< numVertices; i++)
    {
        Position.push_back(vertices[i].getPos());
        TexCoord.push_back(vertices[i].getTexCoord());
    }

    glGenBuffers(NUM_BUFFERS, m_VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_drawCount * sizeof(Position[0]), &Position[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(POSITION_VB);
    glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, m_drawCount * sizeof(TexCoord[0]), &TexCoord[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(TEXCOORD_VB);
    glVertexAttribPointer(TEXCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);

    for(int i=-100;i<1000;i+=2)
    for(int j=-100;j<1000;j+=2)
    {
        translation.push_back(glm::vec3(i,0,j));
    }

    glBindBuffer(GL_ARRAY_BUFFER,m_VertexBufferObject[INSTANCE_VB]);
    glBufferData(GL_ARRAY_BUFFER,translation.size() * sizeof(translation[0]),&translation[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(INSTANCE_VB);
    glVertexAttribPointer(INSTANCE_VB, 3, GL_FLOAT,GL_FALSE,0,0);
    glVertexAttribDivisor(2,1);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(m_VertexArrayObject);
    glDrawArraysInstanced(GL_TRIANGLES,0,m_drawCount,translation.size());
}
