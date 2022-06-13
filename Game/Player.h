/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\Input.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Player : public CS230::GameObject
{
public:
	Player(math::vec2 startpos);
	void Update(double dt);
	void Draw(math::TransformMatrix displayMatrix);
	math::vec2 GetPosition();
	bool CanCollideWith(GameObjectType);
	GameObjectType GetObjectType() { return GameObjectType::Player; }
	std::string GetObjectTypeName() { return "Player"; }
	void ResolveCollision(GameObject* objectB) override;
	bool IsDead() { return isDead; }
	bool GetIsReallyDead() { return isDead; }
	void SetEscape(bool IsEscape) { IsEscape = isEscape; }
	bool GetEscape() { return isEscape; }
	bool GetAlready() { return getAlready; }

private:
	class State_Stop : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "stop"; }
	};

	class State_walking : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "waling"; }
	};

	class State_Jumping : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "sidewayJumping"; }
	};

	class State_GoBackJumping : public State
	{
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void TestForExit(GameObject* object) override;
		std::string GetName() override { return "GoJumping"; }
	};

	void UpdateXYVelocity(double dt);

	GameObject* leftLaser;
	GameObject* rightLaser;
	State_Stop stateStop;
	State_walking stateWalking;
	State_Jumping stateJumping;
	State_GoBackJumping stateGoBackJumping;

	CS230::InputKey moveLeftKey;
	CS230::InputKey moveRightKey;
	CS230::InputKey moveUpKey;
	CS230::InputKey moveDownKey;
	CS230::InputKey ShootKey;

	static constexpr double GoJump = 800;
	static constexpr double hurtTime = 2;
	static constexpr double PI = 3.141592653589793;

	double hurtTimer;
	bool drawPlayer;
	bool isEscape;
	bool isDead;
	bool isReallyEscape;
	bool getAlready;
};