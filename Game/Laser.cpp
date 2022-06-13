/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "Laser.h"
#include "../Engine/Engine.h"
#include "../Engine/Collision.h"
#include "Screens.h"
#include "../Engine/GameObjectManager.h"

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity, int modeNum)
	:GameObject(pos, rotation, scale), ModeNum(modeNum)
{
	if (ModeNum == 2)
	{
		AddGOComponent(new CS230::Sprite("assets/Laser.spt", this));
	}
	else if (ModeNum == 3)
	{
		AddGOComponent(new CS230::Sprite("assets/Laser1.spt", this));
	}

	SetVelocity(laserVelocity);
}

void Laser::Update(double dt)
{
	GameObject::Update(dt);

	if (GetModeNum() == 2)
	{
		if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 ||
			GetPosition().x < -GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 ||
			GetPosition().y > Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 ||
			GetPosition().y < -GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0)
		{
			SetDestroy();
		}
	}
	else if (GetModeNum() == 3)
	{
		if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 ||
			GetPosition().x < -GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0)
		{
			SetDestroy();
		}
	}
}

bool Laser::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor)
	{
		return true;
	}
	if (objectBType == GameObjectType::EnemyShip)
	{
		return true;
	}
	if (objectBType == GameObjectType::Hares)
	{
		return true;
	}
	return false;
}

void Laser::ResolveCollision(GameObject* objectB)
{
	objectB->ResolveCollision(this);
	SetDestroy();
}
