/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Project: CS230
Author: Seulbin Seo
Creation date:  05/09/2022
-----------------------------------------------------------------*/
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ShowCollision.h"
#include "Engine.h"
#include "Collision.h"
#include "TransformMatrix.h"
#include "../Game/GameObjectTypes.h"
#include "../Game/Hero.h"

CS230::GameObject::GameObject() :GameObject({ 0,0 }) {}

CS230::GameObject::GameObject(math::vec2 position) : GameObject(position, 0, { 1, 1 }) {}

CS230::GameObject::GameObject(math::vec2 position, double rotation, math::vec2 scale)
	: velocity{ 0,0 }, position(position), updateMatrix(true), destroyed(false),
	scale(scale), rotation(rotation), currState(&state_nothing) {}

CS230::GameObject::~GameObject()
{
	ClearGOComponents();
}

void CS230::GameObject::Update(double dt)
{
	currState->Update(this, dt);
	if (velocity.x != 0 || velocity.y != 0)
	{
		UpdatePosition(velocity * dt);
	}
	UpdateGOComponents(dt);
	currState->TestForExit(this);
}

void CS230::GameObject::ChangeState(State* newState)
{
	currState = newState;
	currState->Enter(this);
}

void CS230::GameObject::Draw(math::TransformMatrix displayMatrix)
{
	Sprite* spritePtr = GetGOComponent<Sprite>();
	if (spritePtr != nullptr)
	{
		spritePtr->Draw(displayMatrix * GetMatrix());
	}
	ShowCollision* showCollPtr = Engine::GetGSComponent<ShowCollision>();
	Collision* collisionPtr = GetGOComponent<Collision>();
	if (collisionPtr != nullptr && showCollPtr->IsEnabled() == true)
	{
		collisionPtr->Draw(displayMatrix);
	}
}

const math::TransformMatrix& CS230::GameObject::GetMatrix()
{
	if (updateMatrix == true) {
		objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix(scale);
		updateMatrix = false;
	}
	return objectMatrix;
}

//position
const math::vec2& CS230::GameObject::GetPosition() const { return position; }

void CS230::GameObject::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
	updateMatrix = true;
}

bool CS230::GameObject::CanCollideWith(GameObjectType)
{
	return false;
}

bool CS230::GameObject::DoesCollideWith(GameObject* objectB)
{
	if ((GetGOComponent<Collision>() != nullptr)
		&& (objectB->GetGOComponent<Collision>() != nullptr)
		&& GetGOComponent<Collision>()->DoesCollideWith(objectB))
	{
		return true;
	}
	return false;
}

bool CS230::GameObject::DoesCollideWith(math::vec2 point)
{
	if (GetGOComponent<Collision>() != nullptr)
	{
		return GetGOComponent<Collision>()->DoesCollideWith(point);
	}
	return false;
}

bool CS230::GameObject::GetDestroy()
{
	return destroyed;
}

void CS230::GameObject::SetDestroy()
{
	destroyed = true;
}

void CS230::GameObject::ResolveCollision(CS230::GameObject*)
{
	Engine::GetLogger().LogEvent("Collision error");
}


void CS230::GameObject::UpdatePosition(math::vec2 adjustPosition)
{
	position += adjustPosition;
	updateMatrix = true;
}

const math::vec2& CS230::GameObject::GetVelocity() const { return velocity; }

void CS230::GameObject::SetVelocity(math::vec2 newVelocity)
{
	velocity = newVelocity;
}

void CS230::GameObject::UpdateVelocity(math::vec2 adjustVelocity)
{
	velocity += adjustVelocity;
}

const math::vec2& CS230::GameObject::GetScale() const { return scale; }

void CS230::GameObject::SetScale(math::vec2 newScale)
{
	scale = newScale;
	updateMatrix = true;
}

double CS230::GameObject::GetRotation() const { return rotation; }

void CS230::GameObject::SetRotation(double newRotationAmount)
{
	rotation = newRotationAmount;
	updateMatrix = true;
}

void CS230::GameObject::UpdateRotation(double newRotationAmount)
{
	rotation += newRotationAmount;
	updateMatrix = true;
}
