#ifndef BOX_H
#define BOX_H

#include "../Mesh.h"
#include "../Shader.h"

class Box
{
public:
    Box(const float& size);
    ~Box();

    void Draw(const Camera& camera);
private:
    Transform transform;
    Mesh* m_BoxMesh;
    Shader* shader;
};

#endif // BOX_H
