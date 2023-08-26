#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include "../Maths/Maths.h"

class Camera
{
	Vector3D CameraPos;
	Vector3D CameraFront;
	Vector3D CameraUp;
	Matrix4D LookAt;

	float CameraSpeed;

	float yaw,pitch;

	static UINT16 MouseX,MouseY,LastMouseX,LastMouseY;
	static BYTE KeyDown;

	void SetLookAt(const Vector3D& eye,const Vector3D& center,const Vector3D& up);
	void move(const float& dt);
	void rotate(const float& dt);
public:
	Camera(float x=0,float y=0,float z=3);
	Vector3D GetPosition();
	void Update(const float& dt);
	static void Callback(const BYTE& _KeyDown,const UINT16& _MouseX,const UINT16& _MouseY)
	{
		KeyDown = _KeyDown;
		MouseX = _MouseX;
		MouseY = _MouseY;
	}
};

#endif // CAMERA_H
