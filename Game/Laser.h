/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.h
Project: CS230 final project
Author: Seulbin Seo & Junseong Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"


class GameObjectManager;
enum class GameObjectType;

class Laser : public CS230::GameObject {
public:
    static constexpr math::vec2 LaserVelocity = math::vec2{ 0, 600 };
    static constexpr math::vec2 LaserVelocity2 = math::vec2{ 600, 0 };

    Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity, int modeNum);
    void Update(double dt) override;
    std::string GetObjectTypeName() { return "Laser"; }
    virtual GameObjectType GetObjectType() override { return GameObjectType::Laser; }
    virtual bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;
    int GetModeNum() { return ModeNum; }

private:
    int ModeNum;
};