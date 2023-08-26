#ifndef KEYBOARD_H
#define KEYBOARD_H

namespace autoGui
{
	namespace Keyboard
	{
		void keyDown(const char key);
		void keyUp(const char key);
		void hotKey(const char* key,const char ch);
		void pressKey(const char key);
		void typeWrite(const char* str,float time=0);
	}
}

#endif // KEYBOARD_H
