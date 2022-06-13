/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hares.h
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Player;

class Hares : public CS230::GameObject {
public:
    Hares(math::vec2 pos, std::vector<double> patrolNodes, Player* playerPtr);
    GameObjectType GetObjectType() override { return GameObjectType::Hares; }
    std::string GetObjectTypeName() override { return "Hares"; }
    void ResolveCollision(GameObject* objectA) override;
private:
    class State_HangAround : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Hang around"; }
    };
    class State_Angry : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Hang angry"; }
    };
    class State_FallDown : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Fall down"; }
    };

    State_HangAround stateHangAround;
    State_Angry stateAngery;
    State_FallDown stateFallDown;
    Player* playerPtr;

    std::vector<double> patrolNodes;
    int currPatrolNode;
    static constexpr int velocity = 75;
};