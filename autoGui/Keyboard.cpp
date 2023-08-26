#include <windows.h>
#include "Keyboard.h"
#include "Util.h"
#include "Time.h"

namespace autoGui
{
	namespace Keyboard
	{
		// Capital includes all A..Z and other keys which require shift to be pressed to write them
		constexpr bool isCapital(const char& key)
		{
			if(key >= 'A' && key <= 'Z')
				return true;
			else if(key >= '!' && key <= '*')
				return true;
			else if(key >= ':' && key <= '@')
				return true;
			else if(key >= '{' && key <= '~')
				return true;

			return key == '^' || key == '_' || key == '+';
		}

		void keyDown(const char key)
		{
			keybd_event(key,0,KEYEVENTF_EXTENDEDKEY,0);
		}

		void keyUp(const char key)
		{
			keybd_event(key,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
		}

		// change to hotkey(const char key1,const char key2)
		void hotKey(const char* key,const char ch)
		{
			if(strcmp(key,"ctrl")==0)
			{
				keybd_event(VK_CONTROL,0,KEYEVENTF_EXTENDEDKEY | 0,0);
				keybd_event(ch,0,KEYEVENTF_EXTENDEDKEY | 0,0);
				keybd_event(ch,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
				keybd_event(VK_CONTROL,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
			}else if(strcmp(key,"alt")==0)
			{
				keybd_event(VK_MENU,0,KEYEVENTF_EXTENDEDKEY | 0,0);
				keybd_event(ch,0,KEYEVENTF_EXTENDEDKEY | 0,0);
				keybd_event(ch,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
				keybd_event(VK_MENU,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
			}
		}

		void pressKey(const char key)
		{
			if(isCapital(key))
				keybd_event(VK_SHIFT,0,KEYEVENTF_EXTENDEDKEY | 0,0);

			keybd_event(VkKeyScan(key),0,KEYEVENTF_EXTENDEDKEY | 0,0);
			keybd_event(VkKeyScan(key),0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);

			if(isCapital(key))
				keybd_event(VK_SHIFT,0,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
		}

		void typeWrite(const char* str,float time)
		{
			do{
				pressKey(*str);
				Time::WaitMilli(autoGui::Time::SecondsToMilli(time));
			}while(*(++str) != '\0');
		}
	}
}
