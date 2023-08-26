#include "Transform.h"

glm::mat4 Transform::GetModel() const
{
    glm::mat4 posMat = glm::translate(m_pos);
    glm::mat4 scaleMat = glm::scale(m_scale);
    glm::mat4 rotX = glm::rotate(m_rot.x, glm::vec3(1.0,0.0,0.0));
    glm::mat4 rotY = glm::rotate(m_rot.y, glm::vec3(0.0,1.0,0.0));
    glm::mat4 rotZ = glm::rotate(m_rot.z, glm::vec3(0.0,0.0,1.0));
    glm::mat4 rotMat = rotX * rotY * rotZ;

    return posMat * rotMat * scaleMat;
}
