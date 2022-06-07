/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Seulbin Seo
Creation date: 05/23/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

namespace math
{
    struct vec2;
};

class Ball : public CS230::GameObject
{
public:
    Ball(math::vec2 startPos);
    GameObjectType GetObjectType() { return GameObjectType::Ball; }
    std::string GetObjectTypeName() { return "Ball"; }
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;

private:
    class Bounce : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* objectl) override;
        std::string  GetName() override { return "Bounce"; }
    };

    class Land : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string  GetName() override { return "Land"; }
    };

    Bounce stateBounce;
    Land   stateLand;

    static constexpr double bounceVelocity = 600;
};