#ifndef SIMULATION_H
#define SIMULATION_H

#include "Engine.h"
#include <deque>

class Simulation: public Engine{
    Simulation();
    void Update();
    void Draw();
    void Event();
    std::deque<float> wave;
    static Simulation* Instance;
public:
    static Simulation* GetInstance(){return Instance=(Instance!=nullptr)?Instance:new Simulation();}
};

#endif // SIMULATION_H
