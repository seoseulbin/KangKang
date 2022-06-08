/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car3.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/08/2022
-----------------------------------------------------------------*/
#include "Car3.h"
#include "ScreenWrap.h"

Car3::Car3(math::vec2 pos) : GameObject(pos)
{
	AddGOComponent(new CS230::Sprite("assets/Bus.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	currState = &stateDrive2;
	currState->Enter(this);
}

math::vec2 Car3::GetPosition()
{
	return GameObject::GetPosition();
}

bool Car3::CanCollideWith(GameObjectType)
{
	return false;
}

void Car3::UpdateXVelocity(double dt)
{
	SetVelocity(math::vec2{ -drive_vel * dt, 0 });
}

void Car3::State_Drive2::Enter(GameObject*)
{
}

void Car3::State_Drive2::Update(GameObject* object, double dt)
{
	Car3* car3 = static_cast<Car3*>(object);
	car3->UpdateXVelocity(dt);
}

void Car3::State_Drive2::TestForExit(GameObject*) {}
