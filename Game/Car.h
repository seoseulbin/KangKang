/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car.h
Project: CS230 final project
Author: Seulbin Seo & Junseong Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Player;

class Car : public CS230::GameObject
{
public:
	Car(math::vec2 pos,  int CarNum);
	math::vec2 GetPosition();
	bool CanCollideWith(GameObjectType);
	void UpdateXVelocity(double dt);
	GameObjectType GetObjectType() { return GameObjectType::Car; }
	std::string GetObjectTypeName() { return "Car"; }
	int GetCarNum();

	int line1 = 215;
	int line2 = 460;
	int line3 = 705;
	int line4 = 950;
	int line5 = 1150;

private:
	class State_Drive : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Drive"; }
	};
	State_Drive  stateDrive;

	Player* playerPtr;
	int CarNumber;
	
	double drive_vel1 = 5900;
	double drive_vel2 = 6500;
	double drive_vel3 = 8000;
	double drive_vel4 = 7000;
	double drive_vel5 = 7000;
}; 