#include "Timer.h"
#include <windows.h>

Timer* Timer::m_Instance = nullptr;

void Timer::Init()
{
	TicksAtStart = GetTickCount();
}

unsigned long long int Timer::GetTicks()
{
	return GetTickCount() - TicksAtStart;
}

void Timer::Tick()
{
	m_DeltaTime = (GetTicks() - m_LastTime)*(m_Target_FPS/1000);

	if(m_DeltaTime > m_Target_DeltaTime)
		m_DeltaTime = m_Target_DeltaTime;

	m_LastTime = GetTicks();
}
