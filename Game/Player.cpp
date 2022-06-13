/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Seulbin Seo
Creation date: 06/08/2022
-----------------------------------------------------------------*/
#include "Player.h"
#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "../Engine/Collision.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/GameObjectManager.h"
#include "Screens.h"
#include "Player_Anims.h"
#include "GameObjectTypes.h"
#include "Laser.h"
#include "Coin.h"

Player::Player(math::vec2 startpos)
	:GameObject(startpos),
	moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	moveUpKey(CS230::InputKey::Keyboard::Up),
	moveDownKey(CS230::InputKey::Keyboard::Down),
	ShootKey(CS230::InputKey::Keyboard::Space),
	hurtTimer{ 0 }, drawPlayer(false), isDead(false)
{

	AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
	AddGOComponent(new CS230::Sprite("Assets/Laser1.spt", leftLaser));
	AddGOComponent(new CS230::Sprite("Assets/Laser1.spt", rightLaser));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Idle_Anim));
	currState = &stateStop;
	currState->Enter(this);
}

void Player::Update(double dt)
{
	GameObject::Update(dt);

	if (hurtTimer != 0)
	{
		hurtTimer -= dt;
		drawPlayer = !drawPlayer;
	}
	if (hurtTimer <= 0)
	{
		drawPlayer = true;
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
	if (GetPosition().y < GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 - 90)
	{
		SetPosition(
			{ GetPosition().x, Engine::GetGSComponent<CS230::Camera>()->GetPosition().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 - 90 });
		SetVelocity({ GetVelocity().x, 0});
	}
	if ((GetPosition().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) > Engine::GetGSComponent<CS230::Camera>()->GetPosition().y + Engine::GetWindow().GetSize().y)
	{
		SetPosition(
			{ GetPosition().x, Engine::GetGSComponent<CS230::Camera>()->GetPosition().y + Engine::GetWindow().GetSize().y - GetGOComponent<CS230::Sprite>()->GetFrameSize().y   });
		SetVelocity({ 0, GetVelocity().y });
	}

	if (ShootKey.IsKeyReleased() == true && isDead == false)
	{
		Engine::GetGSComponent<CS230::GameObjectManager>()->
			Add(new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->
				GetHotSpot(1)), GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * -Laser::LaserVelocity2, 3));
		Engine::GetGSComponent<CS230::GameObjectManager>()->
			Add(new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->
				GetHotSpot(2)), GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity2, 3));
	}
}

void Player::Draw(math::TransformMatrix displayMatrix)
{
	if (drawPlayer == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

math::vec2 Player::GetPosition()
{
	return GameObject::GetPosition();
}

bool Player::CanCollideWith(GameObjectType objectB)
{
	if (objectB == GameObjectType::Coin)
	{
		return true;
	}
	if (objectB == GameObjectType::Hares)
	{
		return true;
	}
	return false;
}

void Player::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 playerRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	if (GetAlready() == false) {
		switch (objectB->GetObjectType())
		{
			case GameObjectType::Car:
				hurtTimer = hurtTime;
				objectB->ResolveCollision(this);
				SetPosition(math::vec2{ 600, 0 });
				break;
			case GameObjectType::Coin:
				objectB->ResolveCollision(this);
				getAlready = true;

				isEscape = true;
				break;
			case GameObjectType::Hares:
				isDead = true;
				break;
		}
	}

}

void Player::UpdateXYVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		SetPosition({GetPosition().x - GoJump * dt, GetPosition().y});
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		SetPosition({ GetPosition().x + GoJump * dt, GetPosition().y });
	}
	if (moveUpKey.IsKeyDown() == true)
	{
		SetPosition({ GetPosition().x, GetPosition().y + GoJump * dt });
	}
	if (moveDownKey.IsKeyDown() == true)
	{
		SetPosition({ GetPosition().x, GetPosition().y -GoJump * dt });
	}
}

void Player::State_Stop::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Idle_Anim));
}

void Player::State_Stop::Update(GameObject* , double )
{
}

void Player::State_Stop::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveUpKey.IsKeyDown() == true || player->moveDownKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}
	if (player->moveLeftKey.IsKeyDown() == true || player->moveRightKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateWalking);
	}
}

void Player::State_walking::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Walk_Anim));
	if (player->moveLeftKey.IsKeyDown() == true)
	{
		player->SetScale({ -1.0, 1.0 });
	}
	else if (player->moveRightKey.IsKeyDown() == true)
	{
		player->SetScale({ 1.0, 1.0 });
	}
}

void Player::State_walking::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateXYVelocity(dt);
}

void Player::State_walking::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveUpKey.IsKeyDown() == true || player->moveDownKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateJumping);
	}
	if (player->moveLeftKey.IsKeyReleased() == true || player->moveRightKey.IsKeyReleased() == true)
	{
		player->ChangeState(&player->stateStop);
	}
}


void Player::State_Jumping::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Jump_Anim));
}

void Player::State_Jumping::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateXYVelocity(dt);
}

void Player::State_Jumping::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveUpKey.IsKeyReleased() == true || player->moveDownKey.IsKeyReleased() == true)
	{
		player->ChangeState(&player->stateStop);
	}
}

void Player::State_GoBackJumping::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Player_Anims::Player_Dead_Anim));
}

void Player::State_GoBackJumping::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateXYVelocity(dt);
}

void Player::State_GoBackJumping::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveLeftKey.IsKeyDown() == true || player->moveRightKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateWalking);
	}
}
