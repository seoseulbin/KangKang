/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car1.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/08/2022
-----------------------------------------------------------------*/
#include "Car4.h"
#include "ScreenWrap.h"
#include "Player.h"

Car4::Car4(math::vec2 pos) : GameObject(pos)
{
	AddGOComponent(new CS230::Sprite("assets/Car4.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	currState = &stateDrive2;
	currState->Enter(this);
}

math::vec2 Car4::GetPosition()
{
	return GameObject::GetPosition();
}

bool Car4::CanCollideWith(GameObjectType)
{
	return false;
}

void Car4::UpdateXVelocity(double dt)
{
	SetVelocity(math::vec2{ -drive_vel * dt, 0 });
}

void Car4::State_Drive2::Enter(GameObject*)
{
}

void Car4::State_Drive2::Update(GameObject* object, double dt)
{
	Car4* car4 = static_cast<Car4*>(object);
	car4->UpdateXVelocity(dt);
}

void Car4::State_Drive2::TestForExit(GameObject*) {}