#include "Warrior.h"
#include "TextureManager.h"
#include "Input.h"

#define BACKWARD -1
#define FORWARD 1

Warrior::Warrior(Properties* props): Character(props) {
    rigidBody = new RigidBody();
    animation = new Animation();
    animation->setProps(TextureID,1,8,80);
}

void Warrior::Draw() {
    animation->Draw(transform->X,transform->Y,Width,Height);
}

void Warrior::update(float dt) {
    rigidBody->applyForceX(0);
    if(Input::GetInstance()->GetKeydown(SDL_SCANCODE_LEFT))
        rigidBody->applyForceX(5*BACKWARD);
    else if(Input::GetInstance()->GetKeydown(SDL_SCANCODE_RIGHT))
        rigidBody->applyForceX(5*FORWARD);

    rigidBody->Update(dt);
    transform->TranslateX(rigidBody->GetPosition().X);
    animation->update();
}

void Warrior::Clear() {
    TextureManager::GetInstance()->Clear();
}
