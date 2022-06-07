/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/27/2022
-----------------------------------------------------------------*/
#include "Hero.h"
#include "..\Engine\Engine.h"
#include "Mode1.h"
#include "..\Engine\Camera.h" //forward declare
#include "Hero_Anims.h"
#include "..\Engine\Collision.h"
#include "..\Engine\GameObject.h"
#include "Exit.h"
#include "Gravity.h"
#include "GameParticles.h"

Hero::Hero(math::vec2 startPos)
	: GameObject(startPos),
	moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	moveUpKey(CS230::InputKey::Keyboard::Up),
	hurtTimer{ 0 }, drawHero(false), isDead(false), standingOnObject(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/Hero.spt", this));
	AddGOComponent(new Gravity(1000.0));
	currState = &stateIdle;
	currState->Enter(this);
	for (GameObject* i : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		if (DoesCollideWith(i) == true && i->GetObjectType() == GameObjectType::Floor)
		{
			SetPosition(math::vec2{ GetPosition().x ,i->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Top() });
			standingOnObject = i;
			return;
		}
		else
		{
			standingOnObject = nullptr;
		}
	}
}

void Hero::Update(double dt)
{
	GameObject::Update(dt);

	if (hurtTimer != 0)
	{
		hurtTimer -= dt;
		drawHero = !drawHero;
	}
	if (hurtTimer <= 0)
	{
		drawHero = true;
		hurtTimer = 0;
	}

	if (GetPosition().x <= GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2.0)
	{
		SetPosition({ GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2.0, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	if (GetPosition().x + GameObject::GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2.0 > Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x)
	{
		SetPosition(
			{ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GameObject::GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2.0, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
}

void Hero::Draw(math::TransformMatrix displayMatrix)
{
	if (drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

math::vec2 Hero::GetPosition()
{
	return GameObject::GetPosition();
}

bool Hero::CanCollideWith(GameObjectType obj)
{
	if (obj != GameObjectType::Particle)
	{
		return true;
	}
	return false;
}

void Hero::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Ball:
		if (currState != &stateFalling)
		{
			hurtTimer = hurtTime;
			ChangeState(&stateFalling);
			if (GetPosition().x < objectB->GetPosition().x)
			{
				SetPosition(math::vec2{ GetPosition().x - (heroRect.Right() - collideRect.Left()),GetPosition().y });
				SetVelocity(math::vec2{ -x_acceleration, jumpVelocity });
			}
			else if (GetPosition().x > objectB->GetPosition().x)
			{
				SetPosition(math::vec2{ GetPosition().x + (collideRect.Right() - heroRect.Left()),GetPosition().y });
				SetVelocity(math::vec2{ x_acceleration, jumpVelocity });
			}
		}
		else if (currState == &stateFalling)
		{
			if (heroRect.Top() > collideRect.Top())
			{
				SetPosition(math::vec2{ GetPosition().x, GetPosition().y + (collideRect.Top() - heroRect.Bottom()) });
				SetVelocity(math::vec2{ GetVelocity().x, jumpVelocity });
			}
		}
		break;

	case GameObjectType::Bunny:
		if (currState == &stateFalling)
		{
			ChangeState(&stateFalling);
			objectB->ResolveCollision(this);
			Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ GetPosition().x,GetPosition().y + (collideRect.Top() - heroRect.Bottom()) / 2.0 }, { 0,0 }, {0, 0}, 0);
			if (GetPosition().x < objectB->GetPosition().x)
			{
				SetVelocity(math::vec2{ -x_acceleration, jumpVelocity / 2.0 });
			}
			else
			{
				SetVelocity(math::vec2{ x_acceleration, jumpVelocity / 2.0 });
			}
		}
		else if (currState == &stateSkidding)
		{
			Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ GetPosition().x,GetPosition().y + (collideRect.Top() - heroRect.Bottom()) / 2.0 }, { 0,0 }, { 0, 0 }, 0);
			objectB->ResolveCollision(this);
		}
		else
		{
			currState = &stateFalling;
			hurtTimer = hurtTime;
			if (GetPosition().x < objectB->GetPosition().x)
			{
				SetPosition(math::vec2{ GetPosition().x - (heroRect.Right() - collideRect.Left()),GetPosition().y });
				SetVelocity({ -x_acceleration, jumpVelocity / 2 });
			}
			else if (GetPosition().x > objectB->GetPosition().x)
			{
				SetPosition(math::vec2{ GetPosition().x + (collideRect.Right() - heroRect.Left()),GetPosition().y });
				SetVelocity({ x_acceleration, jumpVelocity / 2 });
			}
		}
		break;

	case GameObjectType::Floor:
		[[fallthrough]];

	case GameObjectType::TreeStump:
		if (currState == &stateFalling && heroRect.Top() > collideRect.Top() && objectB->DoesCollideWith(GetPosition()) == true)
		{
			if (GetVelocity().y < -jumpVelocity)
			{
				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ GetPosition().x,GetPosition().y + (collideRect.Top() - heroRect.Bottom()) / 2.0 }, { 0,0 }, { 0, 0 }, 0);
			}
			SetPosition(math::vec2{ GetPosition().x, collideRect.Top() });
			standingOnObject = objectB;
			currState->TestForExit(this);
		}
		else if (GetPosition().x < objectB->GetPosition().x && GetPosition().y < collideRect.Top())
		{
			SetPosition(math::vec2{ GetPosition().x - (heroRect.Right() - collideRect.Left()) , GetPosition().y });
			SetVelocity(math::vec2{ 0, GetVelocity().y });
		}
		else if (GetPosition().x > objectB->GetPosition().x && GetPosition().y < collideRect.Top())
		{
			SetPosition(math::vec2{ GetPosition().x - (heroRect.Left() - collideRect.Right()), GetPosition().y });
			SetVelocity(math::vec2{ 0, GetVelocity().y });
		}
		break;


	case GameObjectType::Trigger:
		objectB->ResolveCollision(this);
		break;
	}
}

void Hero::UpdateXVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		if (GetVelocity().x <= 0 && GetVelocity().x > -x_max)
		{
			UpdateVelocity({ -(x_acceleration * dt), 0 });
		}
		if (GetVelocity().x <= -x_max)
		{
			SetVelocity({ -x_max, GetVelocity().y });
		}
	}

	if (moveRightKey.IsKeyDown() == true)
	{
		if (GetVelocity().x >= 0 && GetVelocity().x < x_max)
		{
			UpdateVelocity({ x_acceleration * dt, 0 });
		}
		if (GetVelocity().x >= x_max)
		{
			SetVelocity({ x_max, GetVelocity().y });
		}
	}

	if (moveRightKey.IsKeyDown() == false && moveLeftKey.IsKeyDown() == false)
	{
		if (GetVelocity().x > 0)
		{
			UpdateVelocity({ -(x_drag * dt), 0 });
			if (GetVelocity().x < 0) {
				SetVelocity({ 0, GetVelocity().y });
			}
		}
		if (GetVelocity().x < 0)
		{
			UpdateVelocity({ (x_drag * dt), 0 });
			if (GetVelocity().x > 0) {
				SetVelocity({ 0, GetVelocity().y });
			}
		}
	}
}

void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr)
	{
		hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
	}
	else
	{
		Engine::GetLogger().LogError("the pointer is nullptr");
	}
}

void Hero::State_Idle::Update(GameObject*, double) {}

void Hero::State_Idle::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveUpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr)
	{
		hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
		if (hero->moveLeftKey.IsKeyDown() == true)
		{
			hero->SetScale({ -1.0, 1.0 });
		}
		else if (hero->moveRightKey.IsKeyDown() == true)
		{
			hero->SetScale({ 1.0, 1.0 });
		}
	}
	else
	{
		Engine::GetLogger().LogError("the pointer is nullptr");
	}
}

void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr)
	{
		if (hero->standingOnObject->DoesCollideWith(hero->GetPosition()) == false)
		{
			hero->ChangeState(&hero->stateFalling);
			hero->standingOnObject = nullptr;
		}
	}
	if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}

	else if (hero->moveUpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}

	else if (hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
	else if (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0)
	{
		hero->ChangeState(&hero->stateSkidding);
	}
}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}

void Hero::State_Skidding::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x > 0)
	{
		hero->UpdateVelocity({ -((x_drag + x_acceleration) * dt), hero->GetVelocity().y });
	}
	else if (hero->GetVelocity().x < 0)
	{
		hero->UpdateVelocity({ ((x_drag + x_acceleration) * dt), hero->GetVelocity().y });
	}
}

void Hero::State_Skidding::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveUpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x <= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		if (hero->GetVelocity().x >= 0)
		{
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == false && hero->moveLeftKey.IsKeyDown() == false)
	{
		hero->ChangeState(&hero->stateRunning);
	}
}

void Hero::State_Jumping::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->SetVelocity({ hero->GetVelocity().x, Hero::jumpVelocity });
	hero->standingOnObject = nullptr;
}

void Hero::State_Jumping::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -(object->GetGOComponent<Gravity>()->GetValue() * dt) });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Jumping::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveUpKey.IsKeyDown() == false)
	{
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
	}
	if (hero->GetVelocity().y <= 0)
	{
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -(object->GetGOComponent<Gravity>()->GetValue() * dt) });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr)
	{
		hero->SetVelocity({ hero->GetVelocity().x, 0 });

		if (hero->GetVelocity().x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else if (hero->GetVelocity().x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		if (hero->GetVelocity().x == 0) 
		{
			hero->ChangeState(&hero->stateIdle);
		}
	}
	if (hero->GetPosition().y < -300)
	{
		hero->isDead = true;
	}
}