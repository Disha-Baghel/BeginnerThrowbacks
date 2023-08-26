#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer{
    public:
        void Tick();
        inline float GetDeltatime(){return DeltaTime;}
        inline static Timer* GetInstance(){return Instance = (Instance != nullptr)?Instance:new Timer();}

    private:
        Timer(){};
        static Timer* Instance;
        float DeltaTime;
        float LastTime;
};

#endif // TIMER_H
