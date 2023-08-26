#ifndef CANVAS_H
#define CANVAS_H

#include "../Window/Window.h"
#include "../OpenGL/OpenGL.h"
#include "../Camera/Camera.h"

class Canvas: private Window, protected OpenGL
{
	BYTE Keys[256] = {0};
protected:
	UINT WIDTH,HEIGHT;
	UINT16 MouseX,MouseY;
	BYTE KeyDown;
private:
	LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam);
	void HandleCamera();
protected:
	void CreateCanvas(const UINT width,const UINT height);
	virtual void Update(float dt){}
	virtual void Render() = 0;
	void SetCanvasName(const std::string Name){SetWindowName(Name);}
	UINT GetTicks();

	bool KeyClicked(BYTE key);
	bool IsKeyDown(BYTE key);
public:
	int Run();
};

#endif // CANVAS_H
