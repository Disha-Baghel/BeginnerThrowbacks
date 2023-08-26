#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	void Init();
	void Tick();
	float GetDeltaTime(){return m_DeltaTime;}
	static Timer* GetInstance(){return m_Instance=(m_Instance != nullptr)?m_Instance:new Timer();}
	void SetFPS(const float FPS){m_Target_FPS = FPS;}
	unsigned long long int GetTicks();
private:
	Timer():m_Target_FPS(60),m_Target_DeltaTime(1.5){}
	static Timer* m_Instance;
	float m_Target_FPS;
	float m_Target_DeltaTime;
	float m_DeltaTime;
	float m_LastTime;
	unsigned long long int  TicksAtStart;
};

#endif // TIMER_H
