/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hares.cpp
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "Hares.h"
#include "Hares_Anims.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "Score.h"
#include "Player.h"

Hares::Hares(math::vec2 pos, std::vector<double> patrolNodes, Player* playerPtr)
	: GameObject(pos), currPatrolNode(0), patrolNodes(patrolNodes), playerPtr(playerPtr)
{
	AddGOComponent(new CS230::Sprite("assets/Hares.spt", this));
	GameObject::GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hares_Anims::Hares_HangAround));
	currState = &stateHangAround;
	currState->Enter(this);
}

void Hares::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Laser)
	{
		ChangeState(&stateFallDown);
	}
	else if (objectA->GetObjectType() == GameObjectType::Player)
	{
		ChangeState(&stateAngery);
	}
}

void Hares::State_HangAround::Enter(GameObject* object)
{
	Hares* hares = static_cast<Hares*>(object);
	hares->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hares_Anims::Hares_HangAround));

	math::rect2 collideRect = object->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 playerRect = hares->playerPtr->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	if (hares->GetPosition().x < hares->patrolNodes[hares->currPatrolNode])
	{
		hares->SetScale(math::vec2{ 1.0, 1.0 });
		hares->SetVelocity(math::vec2{ velocity, 0 });
	}
	if (hares->GetPosition().x > hares->patrolNodes[hares->currPatrolNode])
	{
		hares->SetScale(math::vec2{ -1.0, 1.0 });
		hares->SetVelocity(math::vec2{ -velocity, 0 });
	}
}

void Hares::State_HangAround::Update(GameObject* object, double)
{
	Hares* hares = static_cast<Hares*>(object);
	if (hares->GetPosition().x <= hares->patrolNodes[hares->currPatrolNode] && hares->GetVelocity().x <= 0
		|| hares->GetPosition().x >= hares->patrolNodes[hares->currPatrolNode] && hares->GetVelocity().x >= 0)
	{
		if (hares->patrolNodes.size() - 1 <= hares->currPatrolNode)
		{
			hares->currPatrolNode = 0;
		}
		else
		{
			hares->currPatrolNode++;
		}
		hares->ChangeState(this);
	}
}

void Hares::State_HangAround::TestForExit(GameObject* object)
{
	Hares* hares = static_cast<Hares*>(object);
	math::rect2 collideRect = object->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 playerRect = hares->playerPtr->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	if (collideRect.Bottom() < playerRect.Top()
		|| (collideRect.Top() > playerRect.Bottom() && collideRect.Bottom() < playerRect.Top()))
	{
		if ((hares->playerPtr->GetPosition().x < hares->GetPosition().x && hares->GetVelocity().x < 0)
			|| (hares->playerPtr->GetPosition().x > hares->GetPosition().x && hares->GetVelocity().x > 0))
		{
			if ((hares->playerPtr->GetPosition().x > hares->patrolNodes[hares->currPatrolNode] && hares->playerPtr->GetPosition().x < hares->GetPosition().x)
				|| (hares->playerPtr->GetPosition().x < hares->patrolNodes[hares->currPatrolNode] && hares->playerPtr->GetPosition().x > hares->GetPosition().x))
			{
				hares->ChangeState(&hares->stateAngery);
			}
		}
	}
}

void Hares::State_Angry::Enter(GameObject* object)
{
	Hares* hares = static_cast<Hares*>(object);

	if (hares->GetVelocity().x <= 0)
	{
		hares->SetVelocity(math::vec2{ -velocity * 2 ,0 });
	}
	else if (hares->GetVelocity().x >= 0)
	{
		hares->SetVelocity(math::vec2{ velocity * 2 ,0 });
	}

	hares->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hares_Anims::Heres_Angry));
}

void Hares::State_Angry::Update(GameObject* object, double )
{
	Hares* hares = static_cast<Hares*>(object);
	math::rect2 collideRect = object->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	CS230::RectCollision* player_collisoi = hares->playerPtr->GetGOComponent<CS230::RectCollision>();
	if (player_collisoi != nullptr)
	{
		math::rect2 playerRect = player_collisoi->GetWorldCoorRect();

		if (hares->GetPosition().x >= hares->patrolNodes[hares->currPatrolNode] && hares->GetVelocity().x >= 0
			|| hares->GetPosition().x <= hares->patrolNodes[hares->currPatrolNode] && hares->GetVelocity().x <= 0)
		{
			if (hares->currPatrolNode == hares->patrolNodes.size() - 1)
			{
				hares->currPatrolNode = 0;
			}
			else
			{
				hares->currPatrolNode++;
			}
			if (collideRect.Bottom() > playerRect.Top()
				|| (collideRect.Top() < playerRect.Bottom() && collideRect.Bottom() < playerRect.Top()))
			{
				hares->ChangeState(&hares->stateHangAround);
			}
		}
	}
}

void Hares::State_Angry::TestForExit(GameObject* ) {}

void Hares::State_FallDown::Enter(GameObject* object)
{
	Hares* hares = static_cast<Hares*>(object);
	hares->RemoveGOComponent<CS230::Collision>();
	hares->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hares_Anims::Hares_FallDown));
	hares->SetVelocity(math::vec2{ 0, 0 });

	Engine::GetGSComponent<Score>()->AddScore(10);
}

void Hares::State_FallDown::Update(GameObject* , double) {}

void Hares::State_FallDown::TestForExit(GameObject* ) {}


