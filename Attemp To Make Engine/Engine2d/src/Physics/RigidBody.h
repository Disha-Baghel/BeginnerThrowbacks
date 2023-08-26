#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2d.h"

#define UNIT_MASS    1.0f
#define UNIT_GRAVITY 9.8f

class RigidBody
{
    public:
        RigidBody() {
            Mass    = UNIT_MASS;
            Gravity = UNIT_GRAVITY;
        }

        // setter Gravity & Mass
        inline void setMass(float mass){Mass = mass;}
        inline void setGravity(float gravity){Gravity = gravity;}

        // Force
        inline void applyForce(Vector2d force){Force = force;}
        inline void applyForceX(float Fx){Force.X = Fx;}
        inline void applyForceY(float Fy){Force.Y = Fy;}
        inline void UnSetForce(){Force = Vector2d(0,0);}

        //Friction
        inline void ApplyFriction(Vector2d Fr){Friction = Fr;}
        inline void UnSetFriction(){Friction = Vector2d(0,0);}

        // Getters
        inline float GetMass(){return Mass;}
        inline Vector2d GetPosition(){return Position;}
        inline Vector2d GetVelocity(){return Velocity;}
        inline Vector2d GetAcceleration(){return Acceleration;}

        // Update methods
        void Update(float dt){
            Acceleration.X = (Force.X + Friction.X)/Mass;
            Acceleration.Y = (Gravity + Force.Y)/Mass;
            Velocity = Acceleration*dt;
            Position = Velocity*dt;
        }

    private:

        float Mass;
        float Gravity;

        Vector2d Force;
        Vector2d Friction;

        Vector2d Position;
        Vector2d Velocity;
        Vector2d Acceleration;
};

#endif // RIGIDBODY_H
