/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Coin1.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/10/2022
-----------------------------------------------------------------*/
#include "Coin1.h"
#include "Coin_Anim.h"
#include "../Engine/Engine.h"
#include "Score.h"
#include "../Engine/Collision.h"

Coin1::Coin1(math::vec2 startPos) : GameObject(startPos)
{
	AddGOComponent(new CS230::Sprite("assets/Coin1.spt", this));
	currState = &stateRotate;
	currState->Enter(this);
}

bool Coin1::CanCollideWith(GameObjectType)
{
	return false;
}

void Coin1::ResolveCollision(GameObject* object)
{
	if (object->GetObjectType() == GameObjectType::Player)
	{
		Engine::GetGSComponent<Score>()->AddScore(60);
		RemoveGOComponent<CS230::Collision>();
	}
}

void Coin1::Rotate::Enter(GameObject* object)
{
	Coin1* coin = static_cast<Coin1*>(object);
	coin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Coin_Anim::state_Rotate_Anim));
}

void Coin1::Rotate::Update(GameObject*, double)
{
}

void Coin1::Rotate::TestForExit(GameObject*)
{
}
