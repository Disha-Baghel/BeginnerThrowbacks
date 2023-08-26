#include "Box.h"

Box::Box(const float& size)
{
    glm::vec3 Vertices[] = {
                                glm::vec3(-1,-1,1),glm::vec3(-1,1,1), glm::vec3(1,1,1),
                                glm::vec3(-1,-1,1),glm::vec3( 1,1,1), glm::vec3(1,-1,1),

                                glm::vec3(-1,-1,-1),glm::vec3(-1,1,-1), glm::vec3(-1,1,1),
                                glm::vec3(-1,-1,-1),glm::vec3(-1,1,1), glm::vec3(-1,-1,1),

                                glm::vec3(-1,1,1),glm::vec3(-1,1,-1), glm::vec3(1,1,-1),
                                glm::vec3(-1,1,1),glm::vec3(1,1,-1), glm::vec3(1,1,1),

                                glm::vec3(1,-1,-1),glm::vec3(1,1,-1), glm::vec3(-1,1,-1),
                                glm::vec3(1,-1,-1),glm::vec3(-1,1,-1), glm::vec3(-1,-1,-1),

                                glm::vec3(1,-1,1),glm::vec3(1,1,1), glm::vec3(1,1,-1),
                                glm::vec3(1,-1,1),glm::vec3(1,1,-1), glm::vec3(1,-1,-1),

                                glm::vec3(-1,-1,-1),glm::vec3(-1,-1,1), glm::vec3(1,-1,1),
                                glm::vec3(-1,-1,-1),glm::vec3(1,-1,1), glm::vec3(1,-1,-1),

                            };

    m_BoxMesh = new Mesh(Vertices, sizeof(Vertices)/sizeof(Vertices[0]));

    transform.SetScale(0.5);

    shader = new Shader("Box");
}

Box::~Box()
{
    delete m_BoxMesh;
    delete shader;
}

void Box::Draw(const Camera& camera)
{
    shader->Use();
    shader->Update(transform,camera);
    m_BoxMesh->Draw();
}
