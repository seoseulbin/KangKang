/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Coin1.h
Project: CS230
Author: Seulbin Seo
Creation date: 06/10/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Coin : public CS230::GameObject
{
public:
    Coin(math::vec2 startPos, int coinNum);
    GameObjectType GetObjectType() { return GameObjectType::Coin; }
    std::string GetObjectTypeName() { return "Coin"; }
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;

private:
    class Rotate : public State
    {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* objectl) override;
        std::string  GetName() override { return "Rotate"; }
    };
    Rotate stateRotate;

    static constexpr double bounceVelocity = 600;
    int CoinNum;
};