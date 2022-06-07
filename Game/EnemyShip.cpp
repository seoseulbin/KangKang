/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 6/2/2022
-----------------------------------------------------------------*/
#include "EnemyShip.h"
#include "Ship_Anims.h"
#include "Flame_Anims.h"
#include "GameObjectTypes.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "Score.h"

EnemyShip::EnemyShip(GameObject* player) : player(player),
flameLeft("Assets/flame.spt", this), flameRight("Assets/flame.spt", this), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/enemyShip.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	SetRotation(((rand() % 1024) / 1024.0) * 2 * PI);
	SetPosition(player->GetPosition() + math::RotateMatrix(GetRotation()) * math::vec2{ 0, ((rand() % 1024) / 1024.0) * -250.0 });
}

void EnemyShip::Update(double dt)
{
	flameLeft.Update(dt);
	flameRight.Update(dt);

	math::vec2 distance = math::vec2({ player->GetPosition().x - GetPosition().x, player->GetPosition().y - GetPosition().y });

	if (distance.Normalize().Cross(math::vec2({ math::RotateMatrix(GetRotation()) * math::vec2{ 0,1 } })) > 0.05)
	{
		UpdateRotation(-rotationRate * dt);
	}
	else if (distance.Normalize().Cross(math::vec2({ math::RotateMatrix(GetRotation()) * math::vec2{ 0,1 } })) < -0.05)
	{ 
		UpdateRotation(rotationRate * dt);
	}
	UpdateVelocity({ math::RotateMatrix(GetRotation()) * math::vec2{ 0,accel * dt } });
	UpdateVelocity(-(GetVelocity() * drag * dt));
	UpdatePosition({ GetVelocity() * dt });
	UpdateGOComponents(dt);
}

void EnemyShip::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::GetGOComponent<CS230::Sprite>()->Draw(GetMatrix() * displayMatrix);
	flameLeft.Draw(GetMatrix() * displayMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameRight.Draw(GetMatrix() * displayMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));

	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	CS230::Collision* collisionPtr = GetGOComponent<CS230::Collision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true && collisionPtr != nullptr)
	{
		collisionPtr->Draw(displayMatrix);
	}
}

GameObjectType EnemyShip::GetObjectType()
{
	return GameObjectType::EnemyShip;
}

std::string EnemyShip::GetObjectTypeName()
{
	return "EnemyShip";
}

bool EnemyShip::CanCollideWith(GameObjectType collideAgainstType)
{
	if (collideAgainstType == GameObjectType::Laser)
	{
		return true;
	}
	if (collideAgainstType == GameObjectType::Ship)
	{
		return true;
	}
	return false;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith)
{
	GameObject::GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
	RemoveGOComponent<CS230::Collision>();
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	collidedWith->SetDestroy();

	Engine::GetGSComponent<Score>()->AddScore(300);
}
