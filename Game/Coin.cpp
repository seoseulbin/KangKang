/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Coin1.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/10/2022
-----------------------------------------------------------------*/
#include "Coin.h"
#include "Coin_Anim.h"
#include "../Engine/Engine.h"
#include "Score.h"
#include "../Engine/Collision.h"
#include "Timer.h"

Coin::Coin(math::vec2 startPos, int coinNum) : GameObject(startPos), CoinNum(coinNum)
{
	if (CoinNum == 1)
	{
		AddGOComponent(new CS230::Sprite("assets/Coin1.spt", this));
	}
	else if (CoinNum == 2)
	{
		AddGOComponent(new CS230::Sprite("assets/Coin2.spt", this));
	}
	else if (CoinNum == 3)
	{
		AddGOComponent(new CS230::Sprite("assets/Coin3.spt", this));
	}
	currState = &stateRotate;
	currState->Enter(this);
}


//std::string Coin::GetObjectTypeName()
//{
//	if (CoinNum == 1)
//	{
//		return "Coin1";
//	}
//	else if (CoinNum == 2)
//	{
//		return "Coin2";
//	}
//	else if (CoinNum == 3)
//	{
//		return "Coin3";
//	}
//}

bool Coin::CanCollideWith(GameObjectType)
{
	return false;
}

void Coin::ResolveCollision(GameObject* object)
{
	if (object->GetObjectType() == GameObjectType::Player)
	{
		if (CoinNum == 1)
		{
			Engine::GetGSComponent<Score>()->AddScore(60);
		}
		else if (CoinNum == 2)
		{
			Engine::GetGSComponent<Score>()->AddScore(45);
		}
		else if (CoinNum == 3)
		{
			Engine::GetGSComponent<Score>()->AddScore(30);
		}
		Engine::GetGSComponent<Timer>()->SetTimeStop(true);
		RemoveGOComponent<CS230::Collision>();
	}
}

void Coin::Rotate::Enter(GameObject* object)
{
	Coin* coin = static_cast<Coin*>(object);
	coin->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Coin_Anim::state_Rotate_Anim));
}

void Coin::Rotate::Update(GameObject*, double) {}

void Coin::Rotate::TestForExit(GameObject*) {}
