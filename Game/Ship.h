
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Seulbin Seo
Creation date:  04/24/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ship : public CS230::GameObject
{
public:
	Ship(math::vec2 startPos);
	void Update(double dt)override;
	void Draw(math::TransformMatrix)override;
	bool CanCollideWith(GameObjectType);
	void ResolveCollision(CS230::GameObject* objectB) override;
	GameObjectType GetObjectType() { return GameObjectType::Ship; }
	std::string GetObjectTypeName() { return "Ship"; }
	bool IsDead() { return isDead; }

private:
	CS230::Sprite flameLeft;
	CS230::Sprite flameRight;
	
	GameObject* leftLaser;
	GameObject* rightLaser;

	math::vec2 startPos;

	CS230::InputKey rotateCounterKey;
	CS230::InputKey rotateClockKey;
	CS230::InputKey accelerateKey;
	CS230::InputKey shootKey;

	bool isAccel;
	static constexpr double  accel = 400;
	static constexpr double drag = 1.0f;
	double speed = 3.0; 
	bool isDead;
};