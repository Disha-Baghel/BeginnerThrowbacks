#include <vector>
#include "vec2d.h"
#include "Ray.h"
#include "Boundary.h"
#include <iostream>

class Particle
{
    vec2d pos;
    std::vector<Ray*> rays;
    float heading,fov;
public:
    Particle()
    {
        this->fov = 45;
        this->heading = 0;
        this->pos = {400,250};
        for(float a=-fov/2;a<fov/2;a+=0.5)
        {
            float radian = 3.14/180 * a;
            rays.push_back(new Ray(&pos,radian));
        }
    }

    void move(float amt)
    {
        vec2d vel = vec2d::fromAngle(this->heading);
        vel.setMag(amt);
        vec2d temp = this->pos;
        this->pos.add(vel);
        if(pos.x < 0 || pos.y < 0 || pos.x > 400 || pos.y > 500)
            pos = temp;
    }

    void rotate(float angle)
    {
        this->heading += angle;
        int index = 0;
        for(float a=-fov/2;a<fov/2;a+=0.5)
        {
            rays[index]->setHeading(heading);
            rays[index]->setAngle(a*(3.14/180) + this->heading);
            index++;
        }
    }

    void update(float x,float y)
    {
        if(x>=0 && y>= 0 && x <= 400 && y <= 500)
        {
            pos.x = x;
            pos.y = y;
        }
    }

    std::vector<float> look(SDL_Renderer* renderer,std::vector<Boundary*> walls)
    {
        std::vector<float> scene;
        SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
        for(auto ray:rays)
        {
            float record = 100000;
            vec2d closest;
            for(auto wall:walls)
            {
                const vec2d pt = ray->cast(wall);
                if(pt.x == pos.x && pt.y == pos.y)
                    continue;
                float dist = SDL_sqrt((pos.x-pt.x)*(pos.x-pt.x) + (pos.y-pt.y)*(pos.y-pt.y));
                const float a = ray->Heading() - this->heading;
                dist *= SDL_cos(a);
                if(dist < record)
                {
                    record = dist;
                    closest = pt;
                }
            }
            SDL_SetRenderDrawColor(renderer,255,255,200,200);
            SDL_RenderDrawLine(renderer,this->pos.x,this->pos.y,closest.x,closest.y);

            scene.push_back(record);
        }
        return scene;
    }
};
