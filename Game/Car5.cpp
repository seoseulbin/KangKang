/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car1.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/08/2022
-----------------------------------------------------------------*/
#include "Car5.h"
#include "ScreenWrap.h"
#include "Player.h"

Car5::Car5(math::vec2 pos) : GameObject(pos)
{
	AddGOComponent(new CS230::Sprite("assets/Car5.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	currState = &stateDrive2;
	currState->Enter(this);
}

math::vec2 Car5::GetPosition()
{
	return GameObject::GetPosition();
}

bool Car5::CanCollideWith(GameObjectType)
{
	return false;
}

void Car5::UpdateXVelocity(double dt)
{
	SetVelocity(math::vec2{ drive_vel * dt, 0 });
}

void Car5::State_Drive2::Enter(GameObject* object)
{
	Car5* car5 = static_cast<Car5*>(object);
	car5->SetScale({ -1.0, 1.0 });
}

void Car5::State_Drive2::Update(GameObject* object, double dt)
{
	Car5* car5 = static_cast<Car5*>(object);
	car5->UpdateXVelocity(dt);
}

void Car5::State_Drive2::TestForExit(GameObject*) {}