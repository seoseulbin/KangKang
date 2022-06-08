/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Car2.h
Project: CS230
Author: Seulbin Seo
Creation date: 06/08/2022
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Player;

class Car2 : public CS230::GameObject
{
public:
	Car2(math::vec2 pos);
	math::vec2 GetPosition();
	bool CanCollideWith(GameObjectType);
	void UpdateXVelocity(double dt);
	GameObjectType GetObjectType() { return GameObjectType::Car2; }
	std::string GetObjectTypeName() { return "Car2(blue)"; }

	int line1 = 250;
private:
	class State_Drive2 : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Drive"; }
	};
	State_Drive2  stateDrive2;

	double drive_vel = 6500;
};