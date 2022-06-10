/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car1.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/08/2022
-----------------------------------------------------------------*/
#include "Car1.h"
#include "ScreenWrap.h"
#include "Car1_Anims.h"
#include "Player.h"

Car1::Car1(math::vec2 pos, Player* playerPtr) : GameObject(pos), playerPtr(playerPtr)
{
	AddGOComponent(new CS230::Sprite("assets/Car1.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Car1_Anims::None_Anim));
	currState = &stateDrive;
	currState->Enter(this);
}

math::vec2 Car1::GetPosition()
{
	return GameObject::GetPosition();
}

bool Car1::CanCollideWith(GameObjectType)
{
	return false;
}

void Car1::UpdateXVelocity(double dt)
{
	SetVelocity(math::vec2{ drive_vel * dt, 0 });
}

void Car1::State_Drive::Enter(GameObject* object) 
{
	Car1* car1 = static_cast<Car1*>(object);
	car1->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Car1_Anims::Bright_Anim));
}

void Car1::State_Drive::Update(GameObject* object, double dt)
{
	Car1* car1 = static_cast<Car1*>(object);
	car1->UpdateXVelocity(dt);
}

void Car1::State_Drive::TestForExit(GameObject* ) {}
