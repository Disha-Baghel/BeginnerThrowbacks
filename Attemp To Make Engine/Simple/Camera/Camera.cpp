#include "Camera.h"
#include "GL/gl.h"

BYTE Camera::KeyDown;
UINT16 Camera::MouseX;
UINT16 Camera::MouseY;
UINT16 Camera::LastMouseX;
UINT16 Camera::LastMouseY;

Camera::Camera(float x,float y,float z)
{
	CameraPos.x = x;
	CameraPos.y = y;
	CameraPos.z = z;

	CameraFront.x = 0;
	CameraFront.y = 0;
	CameraFront.z = -1;

	CameraUp.x = 0;
	CameraUp.y = 1;
	CameraUp.z = 0;

	CameraSpeed = 0.1;

	yaw = -90;
	pitch = 0;
}

void Camera::Update(const float& dt)
{
	move(dt);
	rotate(dt);

	SetLookAt(CameraPos,CameraPos + CameraFront,CameraUp);
	glMultMatrixf(LookAt.get());
}

void Camera::move(const float& dt)
{
	switch(KeyDown)
	{
		case 'W': 	CameraPos += CameraSpeed * CameraFront * dt;									break;
		case 'S': 	CameraPos -= CameraSpeed * CameraFront * dt;									break;
		case 'A':	CameraPos -= CameraFront.cross(CameraUp).normalize() * CameraSpeed * dt;		break;
		case 'D':	CameraPos += CameraFront.cross(CameraUp).normalize() * CameraSpeed * dt;		break;
	}
}

void Camera::rotate(const float& dt)
{
	switch(KeyDown)
	{
		case VK_UP:		pitch -= CameraSpeed * dt * 5;	break;
		case VK_DOWN:	pitch += CameraSpeed * dt * 5;	break;
		case VK_LEFT:	yaw += CameraSpeed * dt * 5;	break;
		case VK_RIGHT:	yaw -= CameraSpeed * dt * 5;	break;
	}

	static bool FirstMouse = true;

	if(FirstMouse)
	{
		LastMouseX = MouseX;
		LastMouseY = MouseY;
		FirstMouse = false;
	}

	float OffSetX = LastMouseX - MouseX;
	float OffsetY = MouseY - LastMouseY;
	LastMouseX = MouseX;
	LastMouseY = MouseY;

	const float sensitivity = 0.2;
	OffSetX *= sensitivity;
	OffsetY *= sensitivity;

	yaw += OffSetX;
	pitch += OffsetY;

	if(pitch > 89.9)
		pitch = 89.9;
	else if(pitch < -89.9)
		pitch = -89.9;

	Vector3D Direction;
	Direction.x = cos(ToRadians(yaw)) * cos(ToRadians(pitch));
	Direction.y = sin(ToRadians(pitch));
	Direction.z = sin(ToRadians(yaw)) * cos(ToRadians(pitch));
	CameraFront = Direction.normalize();
}

void Camera::SetLookAt(const Vector3D& eye,const Vector3D& center,const Vector3D& up)
{
	Vector3D f = (center - eye).normalize();
	Vector3D s = (f.cross(up)).normalize();
	Vector3D u = s.cross(f);

	LookAt.setColumn(0,s);
	LookAt.setColumn(1,u);
	LookAt.setColumn(2,-f);
	LookAt.setColumn(3,{-s.dot(eye),-u.dot(eye),f.dot(eye),1});
}
