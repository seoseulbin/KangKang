/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car2.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/08/2022
-----------------------------------------------------------------*/
#include "Car2.h"
#include "ScreenWrap.h"

Car2::Car2(math::vec2 pos) : GameObject(pos)
{
	AddGOComponent(new CS230::Sprite("assets/Car2.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	currState = &stateDrive2;
	currState->Enter(this);
}

math::vec2 Car2::GetPosition()
{
	return GameObject::GetPosition();
}

bool Car2::CanCollideWith(GameObjectType)
{
	return false;
}

void Car2::UpdateXVelocity(double dt)
{
	SetVelocity(math::vec2{ -drive_vel * dt, 0 });
}

void Car2::State_Drive2::Enter(GameObject* )
{
}

void Car2::State_Drive2::Update(GameObject* object, double dt)
{
	Car2* car2 = static_cast<Car2*>(object);
	car2->UpdateXVelocity(dt);
}

void Car2::State_Drive2::TestForExit(GameObject*) {}
