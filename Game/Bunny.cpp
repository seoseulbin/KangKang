/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/03/2022
-----------------------------------------------------------------*/
#include "Bunny.h"
#include "../Engine/Collision.h"
#include "Bunny_Anims.h"
#include "Mode1.h"
#include "Score.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"
#include "Hero.h"

Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr)
	: GameObject(pos), currPatrolNode(0), patrolNodes(patrolNodes), heroPtr(heroPtr)
{
	AddGOComponent(new CS230::Sprite("assets/bunny.spt", this));
	GameObject::GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	currState = &statePatrol;
	currState->Enter(this);
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		ChangeState(&stateDead);
	}
}

void Bunny::State_Patrol::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));

	if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->SetScale(math::vec2{ 1.0, 1.0 });
		bunny->SetVelocity(math::vec2{ velocity, 0 });
	}
	if (bunny->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->SetScale(math::vec2{ -1.0, 1.0 });
		bunny->SetVelocity(math::vec2{ -velocity, 0 });
	}
}

void Bunny::State_Patrol::Update(GameObject* object, double)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x <= 0
		|| bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x >= 0)
	{
		if (bunny->patrolNodes.size() - 1 <= bunny->currPatrolNode)
		{
			bunny->currPatrolNode = 0;
		}
		else
		{
			bunny->currPatrolNode++;
		}
		bunny->ChangeState(this);
	}
}

void Bunny::State_Patrol::TestForExit(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if (bunny->heroPtr->GetPosition().y == bunny->GetPosition().y)
	{
		if ((bunny->heroPtr->GetPosition().x < bunny->GetPosition().x && bunny->GetVelocity().x < 0)
			|| (bunny->heroPtr->GetPosition().x > bunny->GetPosition().x && bunny->GetVelocity().x > 0))
		{
			if ((bunny->heroPtr->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode] && bunny->heroPtr->GetPosition().x < bunny->GetPosition().x)
				|| (bunny->heroPtr->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode] && bunny->heroPtr->GetPosition().x > bunny->GetPosition().x))
			{
				bunny->ChangeState(&bunny->stateAttack);
			}
		}
	}
}

void Bunny::State_Attack::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if (bunny->GetVelocity().x <= 0)
	{
		bunny->SetVelocity(math::vec2{ -velocity * 2.0 ,0 });
	}
	else if (bunny->GetVelocity().x >= 0)
	{
		bunny->SetVelocity(math::vec2{ velocity * 2.0 ,0 });
	}

	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));
}

void Bunny::State_Attack::Update(GameObject* object, double)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x <= 0
		|| bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x >= 0)
	{
		bunny->ChangeState(&bunny->statePatrol);
	}
}

void Bunny::State_Attack::TestForExit(GameObject*) {}

void Bunny::State_Dead::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->RemoveGOComponent<CS230::Collision>();
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	bunny->SetVelocity(math::vec2{ 0, 0 });

	Engine::GetGSComponent<Score>()->AddScore(100);
}

void Bunny::State_Dead::Update(GameObject*, double) {}

void Bunny::State_Dead::TestForExit(GameObject*) {}
