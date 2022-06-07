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

Player::Player(math::vec2 startpos)
	:GameObject(startpos),
	moveLeftKey(CS230::InputKey::Keyboard::Left),
	moveRightKey(CS230::InputKey::Keyboard::Right),
	moveUpKey(CS230::InputKey::Keyboard::Up),
	moveDownKey(CS230::InputKey::Keyboard::Down)
{
	AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
	currState = &stateStop;
	currState->Enter(this);
}

void Player::Update(double dt)
{
	GameObject::Update(dt);
}

void Player::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::Draw(displayMatrix);
}

math::vec2 Player::GetPosition()
{
	return GameObject::GetPosition();
}

bool Player::CanCollideWith(GameObjectType)
{
	return false;
}

void Player::UpdateXYVelocity(double dt)
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		UpdatePosition({ -GoJump * dt, 0 });
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		UpdatePosition({ GoJump * dt, 0 });
	}
	if (moveUpKey.IsKeyDown() == true)
	{
		UpdatePosition({ 0, GoJump * dt });
	}
	if (moveDownKey.IsKeyDown() == true)
	{
		UpdatePosition({ 0, -GoJump * dt });
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
