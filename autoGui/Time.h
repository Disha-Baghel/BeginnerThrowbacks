#ifndef TIME_H
#define TIME_H

namespace autoGui
{
	namespace Time
	{
		const int SecondsToNano(float time);
		const int SecondsToMicro(float time);
		const int SecondsToMilli(float time);
		void WaitNano(int time);
		void WaitMicro(int time);
		void WaitMilli(int time);
		void WaitSecond(int time);
		void WaitMinute(int time);
		void WaitHour(int time);
	}
}

#endif // TIME_H
