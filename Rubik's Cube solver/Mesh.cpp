#include "Mesh.h"
#include <GL/glew.h>
#include <vector>

Mesh::Mesh(const glm::vec3* Vertices, const unsigned int& NumVertices)
{
    DrawCount = NumVertices;

    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);

    std::vector<glm::vec3> Positions;

    for(unsigned int i=0; i<DrawCount; i++)
        Positions.push_back(Vertices[i]);

    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexArrayObject);
    glBufferData(GL_ARRAY_BUFFER, DrawCount * sizeof(Positions), &Positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindVertexArray(VertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, DrawCount);
}
