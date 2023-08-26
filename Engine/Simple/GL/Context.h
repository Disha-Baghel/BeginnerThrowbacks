#include <windows.h>
#include <string>

namespace Simple
{
	class Window;
	class Context
	{
	public:
		Context(HDC dc, uint16_t Width,uint16_t Height);
		~Context();
		void Resize(uint16_t Width,uint16_t Height);
		void Activate();
		void ClearColor(int hexRGB);
		void ClearColor(UCHAR r,UCHAR g,UCHAR b);
		void Clear();
		void ResetMatrix();
		void Present();
		const float Time();
	private:
		friend class Window;
		HDC hDeviceContext;
		HGLRC hRenderContext;
		LARGE_INTEGER TimeOffset;
		bool owned;
	};
}
