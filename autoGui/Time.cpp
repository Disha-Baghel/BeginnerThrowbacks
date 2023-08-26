#include <chrono>
#include <thread>
#include "Time.h"

namespace autoGui
{
	namespace Time
	{
		const int SecondsToNano(float time)
		{
			return time * 1000000000;
		}

		const int SecondsToMicro(float time)
		{
			return time* 1000000;
		}

		const int SecondsToMilli(float time)
		{
			return time*1000;
		}

		void WaitNano(int time)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(time));
		}

		void WaitMicro(int time)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(time));
		}

		void WaitMilli(int time)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
		}

		void WaitSecond(int time)
		{
			std::this_thread::sleep_for(std::chrono::seconds(time));
		}

		void WaitMinute(int time)
		{
			std::this_thread::sleep_for(std::chrono::minutes(time));
		}

		void WaitHour(int time)
		{
			std::this_thread::sleep_for(std::chrono::hours(time));
		}
	}
}
