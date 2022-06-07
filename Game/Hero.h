/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Seulbin Seo
Creation date: 05/18/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Hero : public CS230::GameObject
{
public:
	Hero(math::vec2 startPos);
	void Update(double dt);
	void Draw(math::TransformMatrix displayMatrix);
	math::vec2 GetPosition();
	bool CanCollideWith(GameObjectType);
	GameObjectType GetObjectType() { return GameObjectType::Hero; }
	std::string GetObjectTypeName() { return "Hero"; }
	void ResolveCollision(GameObject* objectB) override;
	bool IsDead() { return isDead; }

private:
	class State_Idle : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Idle"; }
	};

	class State_Running : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Running"; }
	};

	class State_Skidding : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Skidding"; }
	};

	class State_Jumping : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Jumping"; }
	};

	class State_Falling : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "Falling"; }
	};

	State_Idle stateIdle;
	State_Running stateRunning;
	State_Skidding stateSkidding;
	State_Jumping stateJumping;
	State_Falling stateFalling;

	void UpdateXVelocity(double dt);

	CS230::InputKey moveLeftKey;
	CS230::InputKey moveRightKey;
	CS230::InputKey moveUpKey;

	static constexpr double jumpVelocity = 700;
	static constexpr double x_acceleration = 400.0;
	static constexpr double x_drag = 700.0;
	static constexpr double x_max = 700.0;
	static constexpr double hurtTime = 2;

	double hurtTimer;
	bool drawHero;
	bool isDead;
	GameObject* standingOnObject;
};
