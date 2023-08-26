#include "Camera.h"
#include "../InputManager/InputManager.h"
#include <SDL2/SDL.h>

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
    this->m_pos = pos;
    this->m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
    this->m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->m_projection = glm::perspective(fov, aspect, zNear, zFar);

    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_CaptureMouse(SDL_TRUE);

    m_yaw = -90;
    m_pitch = 0;

    m_sensitivity = 0.1;

    m_firstTime = true;

    m_speed = 0.5;
}

void Camera::Update()
{
    if(m_firstTime)
    {
        SDL_GetMouseState(&m_lastxPos,&m_lastyPos);
        m_firstTime = false;
    }

    int xPos,yPos;
    SDL_GetMouseState(&xPos,&yPos);

    float xOffSet = xPos - m_lastxPos;
    float yOffSet = m_lastyPos - yPos;
    m_lastxPos = xPos;
    m_lastyPos = yPos;

    m_yaw += xOffSet * m_sensitivity;
    m_pitch += yOffSet * m_sensitivity;

    if(m_pitch > 89.0)
        m_pitch = 89.0;
    else if(m_pitch < -89.0)
        m_pitch = -89.0;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward = glm::normalize(direction);

    if(InputInstance->KeyDown(SDLK_w))
         m_pos += (m_speed) * m_forward;
    else if(InputInstance->KeyDown(SDLK_s))
        m_pos -= (m_speed) * m_forward;
    else if(InputInstance->KeyDown(SDLK_d))
        m_pos += (m_speed) * glm::normalize(glm::cross(m_forward,m_up));
    else if(InputInstance->KeyDown(SDLK_a))
        m_pos -= (m_speed) * glm::normalize(glm::cross(m_forward,m_up));
    else if(InputInstance->KeyDown(SDLK_SPACE))
        m_pos += (m_speed) * glm::normalize(m_up);
}
