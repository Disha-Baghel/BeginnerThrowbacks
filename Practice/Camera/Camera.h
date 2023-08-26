#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

    glm::mat4 GetProjection() const
	{
		return m_projection;
	}

    glm::mat4 GetView() const
	{
	    return glm::lookAt(m_pos, m_pos + m_forward, m_up);
	}

	void Update();

protected:
private:
	glm::mat4 m_projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	float m_sensitivity;
	float m_yaw, m_pitch;

	bool m_firstTime;
	int m_lastxPos,m_lastyPos;

	float m_speed;
};

#endif
