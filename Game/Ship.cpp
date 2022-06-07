/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/18/2022
-----------------------------------------------------------------*/
#include "Ship.h"
#include "../Engine/Engine.h"
#include "Flame_Anims.h"
#include "ScreenWrap.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "Ship_Anims.h"
#include "Laser.h"
#include "../Engine/GameObjectManager.h"

Ship::Ship(math::vec2 startPos) 
	:GameObject(startPos, GetRotation(), GetScale()),
	rotateCounterKey(CS230::InputKey::Keyboard::A),
	rotateClockKey(CS230::InputKey::Keyboard::D),
	accelerateKey(CS230::InputKey::Keyboard::W),
	shootKey(CS230::InputKey::Keyboard::Space),
	isAccel(false), flameLeft("Assets/flame.spt", this), flameRight("Assets/flame.spt", this), isDead(false)
{
	AddGOComponent(new ScreenWrap(*this));
	AddGOComponent(new CS230::Sprite("Assets/Ship.spt", this));
	AddGOComponent(new CS230::Sprite("Assets/Laser.spt", leftLaser));
	AddGOComponent(new CS230::Sprite("Assets/Laser.spt", rightLaser));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
}

void Ship::Update(double dt)
{
	GetGOComponent<CS230::Sprite>()->Update(dt);
	if (IsDead() == false)
	{
		flameLeft.Update(dt);
		flameRight.Update(dt);

		if (rotateCounterKey.IsKeyDown() == true)
		{
			UpdateRotation({ speed * dt });
		}
		if (rotateClockKey.IsKeyDown() == true)
		{
			UpdateRotation({ -speed * dt });
		}
		if (accelerateKey.IsKeyDown() == true)
		{
			UpdateVelocity(math::RotateMatrix{ GetRotation() } *math::vec2{ 0, accel * dt });

			if (isAccel == true)
			{
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			}
			isAccel = false;
		}
		if (isAccel == false)
		{
			flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			isAccel = true;
		}
		if (shootKey.IsKeyReleased() == true && isDead == false)
		{
			Engine::GetGSComponent<CS230::GameObjectManager>()->
				Add(new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->
					GetHotSpot(3)), GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
			Engine::GetGSComponent<CS230::GameObjectManager>()->
				Add(new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->
					GetHotSpot(4)), GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
		}
	}
	UpdateVelocity(-(GetVelocity() * Ship::drag * dt));
	UpdatePosition({ GetVelocity() * dt });
	SetScale({ 0.75, 0.75 });
	UpdateGOComponents(dt);
}

void Ship::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::GetGOComponent<CS230::Sprite>()->Draw(GetMatrix());
	flameLeft.Draw(GetMatrix() * displayMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameRight.Draw(GetMatrix()* displayMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));

	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	CS230::Collision* collisionPtr = GetGOComponent<CS230::Collision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true && collisionPtr != nullptr)
	{
		collisionPtr->Draw(displayMatrix);
	}
}

bool Ship::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Meteor)
	{
		return true;
	}
	if (objectBType == GameObjectType::EnemyShip)
	{
		return true;
	}
	return false;
}

void Ship::ResolveCollision(CS230::GameObject*)
{
	GameObject::GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
	RemoveGOComponent<CS230::Collision>();
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	isDead = true;
}


