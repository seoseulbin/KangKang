/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/23/2022
-----------------------------------------------------------------*/
#include "Ball.h"
#include "..\Engine\Engine.h"
#include "Ball_Anims.h"
#include "../Engine/Collision.h"
#include "Gravity.h"

Ball::Ball(math::vec2 startPos) : GameObject(startPos)
{
    AddGOComponent(new CS230::Sprite("assets/Ball.spt", this));
    AddGOComponent(new Gravity(1000.0));
    currState = &stateBounce;
    currState->Enter(this);
}

bool Ball::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::Floor) {
        return true;
    }
    return false;
}

void Ball::ResolveCollision(CS230::GameObject* objectB) {
    if (objectB->GetObjectType() == GameObjectType::Floor) {
        CS230::RectCollision* collideRect =
            static_cast<CS230::RectCollision*>(objectB->GetGOComponent<CS230::RectCollision>());
        SetPosition({ GetPosition().x, collideRect->GetWorldCoorRect().Top() });
        SetVelocity({ GetVelocity().x, 0 });
        ChangeState(&stateLand);
    }
}

void Ball::Bounce::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
    ball->UpdateVelocity({ 0, Ball::bounceVelocity });
}

void Ball::Bounce::Update(GameObject* object, double dt)
{
    Ball* ball = static_cast<Ball*>(object);
    double gravity = ball->GetGOComponent<Gravity>()->GetValue();
    ball->UpdateVelocity({ 0, - gravity * dt});
}

void Ball::Bounce::TestForExit(GameObject*) {}

void Ball::Land::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}

void Ball::Land::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {}

void Ball::Land::TestForExit(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true) 
    {
        ball->ChangeState(&ball->stateBounce);
    }
}
