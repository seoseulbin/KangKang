/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/03/2022
-----------------------------------------------------------------*/
#include "Meteor.h"
#include "..\Engine\Engine.h"
#include "ScreenWrap.h"
#include "Splash.h"
#include "Meteor_Anims.h"
#include "Score.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "GameParticles.h"

Meteor::Meteor() : GameObject({ 0, 0 }), health(100), size(1)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	SetPosition
	
	(math::vec2{ static_cast<double>(rand() % Engine::GetWindow().GetSize().x), static_cast<double>(rand() % Engine::GetWindow().GetSize().y) });
	SetRotation(rand() / (RAND_MAX / ((2 * PI) - 0)));
	SetVelocity({ static_cast<double>((-100) + rand() / (RAND_MAX / (200))), static_cast<double>((-100) + rand() / (RAND_MAX / (200))) });
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
}

Meteor::Meteor(Meteor& original) : GameObject(original.GetPosition()), health(100), size(original.size)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
	size += 1;
	switch (size)
	{
	case 2:
		SetScale(math::vec2{ 0.5 + rand() / (RAND_MAX / (1 - 0.5)) });
		break;
	case 3:
		SetScale(math::vec2{ 0.25 + rand() / (RAND_MAX / (1 - 0.25)) });
		break;
	}
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	GetGOComponent<ScreenWrap>()->Update(dt);
	if (GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Meteor_Anim::Fade_Anim) && GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		SetDestroy();
	}
}

GameObjectType Meteor::GetObjectType()
{
	return GameObjectType::Meteor;
}

std::string Meteor::GetObjectTypeName()
{
	return "Meteor";
}

void Meteor::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Laser)
	{
		math::vec2 VecterPosition = objectB->GetPosition() - GetPosition();
		Engine::GetGSComponent<HitEmitter>()->Emit(1, VecterPosition.Normalize() * GetGOComponent<CS230::CircleCollision>()->GetRadius() + GetPosition(), GetVelocity(), {0, 0}, 0);
		math::vec2 vectorToobject = (objectB->GetPosition() - GetPosition()).Normalize();
		math::vec2 collision_point = vectorToobject * GetGOComponent<CS230::CircleCollision>()->GetRadius();
		math::vec2 object_velocity = objectB->GetVelocity().Normalize();

		Engine::GetGSComponent<MeteorBitEmitter>()->Emit(10, collision_point + GetPosition(), GetVelocity(), (vectorToobject * 2.0 + object_velocity) * 50.0, PI / 2.0);
		health -= 10;
	}

	if (health == 0)
	{
		if (size < 3)
		{
			Meteor* MeteorLeft = new Meteor(*this);
			MeteorLeft->SetVelocity({ math::RotateMatrix(-PI / 6.0) * GetVelocity() });
			Meteor* MeteorRight = new Meteor(*this);
			MeteorRight->SetVelocity({ math::RotateMatrix(PI / 6.0) * GetVelocity() });

			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(MeteorLeft);
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(MeteorRight);

			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
			RemoveGOComponent<CS230::Collision>();
			Engine::GetGSComponent<Score>()->AddScore(100 * size);
		}
		if (size == 3)
		{
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
			RemoveGOComponent<CS230::Collision>();
			Engine::GetGSComponent<Score>()->AddScore(100 * size);
		}
	}
	else
	{
		UpdateVelocity({ 0.01 * objectB->GetVelocity() });
	}
}

