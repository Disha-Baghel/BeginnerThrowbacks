#include "Context.h"
#include "../Math/Math.h"
#include <GL/gl.h>

namespace Simple
{
	void Context::ClearColor(int hexRGB)
	{
		UCHAR r = hexRGB>>16 & 0xff;
		UCHAR g = hexRGB>>8  & 0xff;
		UCHAR b = hexRGB	 & 0xff;

		ClearColor(r,g,b);
	}

	void Context::ClearColor(UCHAR r,UCHAR g,UCHAR b)
	{
		float R = map(r,0,255,0,1);
		float G = map(g,0,255,0,1);
		float B = map(b,0,255,0,1);

		glClearColor(R,G,B,1.0f);
	}

	void Context::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Context::ResetMatrix()
	{
		glLoadIdentity();
	}
}
