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

Player::Player(math::vec2 startpos)
	:GameObject(startpos),
	moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	moveUpKey(CS230::InputKey::Keyboard::Up),
	moveDownKey(CS230::InputKey::Keyboard::Down),
	hurtTimer{ 0 }, drawPlayer(false), isDead(false)
{
	AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
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

	if (GetPosition().x < GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 - 100)
	{
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 -120, GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	if ((GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) > Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - 50)
	{
		SetPosition(
			{ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 -50, GetPosition().y });
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

bool Player::CanCollideWith(GameObjectType)
{
	return false;
}

void Player::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Car:
		if (GetPosition().x > objectB->GetPosition().x)
		{
			hurtTimer = hurtTime;
		}
		else if (GetPosition().x < objectB->GetPosition().x)
		{
			hurtTimer = hurtTime;
		}
		break;
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

void Player::State_Stop::Enter(GameObject* )
{
}

void Player::State_Stop::Update(GameObject* , double )
{
}

void Player::State_Stop::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveUpKey.IsKeyDown() == true || player->moveDownKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateGoBackJumping);
	}
	if (player->moveLeftKey.IsKeyDown() == true || player->moveRightKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateSidewayJumping);
	}
}

void Player::State_sidewayJumping::Enter(GameObject*)
{
	//점프하는 애니메이션 넣기
}

void Player::State_sidewayJumping::Update(GameObject* object, double dt)
{
	Player* player = static_cast<Player*>(object);
	player->UpdateXYVelocity(dt);
}

void Player::State_sidewayJumping::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	if (player->moveUpKey.IsKeyDown() == true || player->moveDownKey.IsKeyDown() == true)
	{
		player->ChangeState(&player->stateGoBackJumping);
	}
	player->ChangeState(&player->stateStop);
}

void Player::State_GoBackJumping::Enter(GameObject*)
{
	//옆으로 점프 애니메이션 넣기
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
		player->ChangeState(&player->stateSidewayJumping);
	}
}
