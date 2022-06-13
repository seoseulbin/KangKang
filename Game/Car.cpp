/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car.cpp
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "Car.h"
#include "ScreenWrap.h"
#include "Car1_Anims.h"
#include "Player.h"

Car::Car(math::vec2 pos, int CarNum) : GameObject(pos), CarNumber(CarNum), playerPtr(playerPtr)
{
	if (CarNumber == 1)
	{
		AddGOComponent(new CS230::Sprite("assets/Car1.spt", this));
	}
	else if (CarNumber == 2)
	{
		AddGOComponent(new CS230::Sprite("assets/Car2.spt", this));
	}
	else if (CarNumber == 3)
	{
		AddGOComponent(new CS230::Sprite("assets/Bus.spt", this));
	}
	else if (CarNumber == 4)
	{
		AddGOComponent(new CS230::Sprite("assets/Car4.spt", this));
	}
	else if (CarNumber == 5)
	{
		AddGOComponent(new CS230::Sprite("assets/Car5.spt", this));
	}
	AddGOComponent(new ScreenWrap(*this));
	if (CarNumber == 1)
	{
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Car1_Anims::None_Anim));
	}
	currState = &stateDrive;
	currState->Enter(this);
}

math::vec2 Car::GetPosition()
{
	return GameObject::GetPosition();
}

bool Car::CanCollideWith(GameObjectType)
{
	return false;
}

void Car::UpdateXVelocity(double dt)
{
	if (CarNumber == 1)
	{
		SetVelocity(math::vec2{ drive_vel1 * dt, 0 });
	}
	else if (CarNumber == 2)
	{
		SetVelocity(math::vec2{ -drive_vel2 * dt, 0 });
	}
	else if (CarNumber == 3)
	{
		SetVelocity(math::vec2{ -drive_vel3 * dt, 0 });
	}
	else if (CarNumber == 4)
	{
		SetVelocity(math::vec2{ -drive_vel4 * dt, 0 });
	}
	else if (CarNumber == 5)
	{
		SetVelocity(math::vec2{ drive_vel5 * dt, 0 });
	}
}

//std::string Car::GetObjectTypeName()
//{
//	if ( GetCarNum() == 1)
//	{
//		return "Car1(police)";
//	}
//	else if (GetCarNum() == 2)
//	{
//		return "Car2(blue)";
//	}
//	else if (GetCarNum() == 3)
//	{
//		return "Car3(truck)";
//	}
//	else if (GetCarNum() == 4)
//	{
//		return "Car4(excavator)";
//	}
//	else if (GetCarNum() == 5)
//	{
//		return "Car5(pink)";
//	}
//}

int Car::GetCarNum()
{
	return CarNumber;
}

void Car::State_Drive::Enter(GameObject* object)
{
	Car* car = static_cast<Car*>(object);
	if (car->GetCarNum() == 1)
	{
		car->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Car1_Anims::Bright_Anim));
	}
	if (car->GetCarNum() == 5)
	{
		car->SetScale({ -1.0, 1.0 });
	}
}

void Car::State_Drive::Update(GameObject* object, double dt)
{
	Car* car = static_cast<Car*>(object);
	car->UpdateXVelocity(dt);
}

void Car::State_Drive::TestForExit(GameObject* ) {}
