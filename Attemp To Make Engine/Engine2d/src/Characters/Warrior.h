#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Warrior: public Character {

  public:
    Warrior(Properties* props);

    virtual void Draw();
    virtual void Clear();
    virtual void update(float dt);
  private:

    Animation* animation;
    RigidBody* rigidBody;
};

#endif // WARRIOR_H
