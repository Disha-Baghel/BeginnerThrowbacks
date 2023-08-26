#ifndef MOON_H
#define MOON_H

#include "Body.h"

class Moon: public Body{
public:
    Moon();
    void Update();
    void Render();
};

#endif // MOON_H
