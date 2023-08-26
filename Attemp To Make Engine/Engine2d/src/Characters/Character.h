#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character: public GameObject {
  public:
    Character(Properties* props): GameObject(props) {}

    virtual void Draw() = 0;
    virtual void update(float dt) = 0;
    virtual void Clear() = 0;

  protected:
    std::string Name;
};

#endif // CHARACTER_H
