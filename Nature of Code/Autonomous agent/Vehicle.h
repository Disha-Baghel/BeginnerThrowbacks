#include "Engine.h"
#include <iostream>

class Vehicle
{
    Vec2d location;
    Vec2d velocity;
    Vec2d acceleration;
    float size,maxSpeed,maxForce;
public:
    Vehicle(float x,float y,float s)
    {
        location = {x,y};
        size = s;
        location = {0,0};
        acceleration = {0,0};
        maxSpeed = 0.3;
        maxForce = 0.1;
    }

    void applyForce(Vec2d f)
    {
        acceleration += f;
    }

    void seek(Vec2d target)
    {
        Vec2d desired = target - location;
        float d = desired.mag();
        if(d > maxSpeed)
        {
            desired.setMag(maxSpeed);
        }
        Vec2d steer = desired - velocity;
        d = steer.mag();
        if(d > maxForce)
        {
            steer.setMag(maxForce);
        }
        applyForce(steer);
    }

    void update()
    {
        velocity += acceleration;
        location += velocity;
        acceleration *= 0;
    }

    void display()
    {
        float ang = velocity.heading() + M_PI/2;
        std::vector<Vec2d> points;
        points.push_back({0,-size});
        points.push_back({-size,size});
        points.push_back({size,size});
        for(int i=0;i<points.size();i++)
        {
            points[i].rotate(ang);
            points[i] += location;
        }
        Engine::DrawShape(points);
    }
};
