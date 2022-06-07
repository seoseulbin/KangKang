/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 4/29/2022
-----------------------------------------------------------------*/
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Engine.h"
#include "..\Game\GameObjectTypes.h"
#include "Sprite.h"

CS230::GameObjectManager::~GameObjectManager()
{
	for (GameObject* i : gameObjects)
	{
		delete i;
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void CS230::GameObjectManager::Update(double dt)
{
	std::list<GameObject*> destroyList;
	for (GameObject* i : gameObjects)
	{
		if (i->GetDestroy() == true)
		{
			destroyList.push_back(i);
		}
		i->Update(dt);
	}
	for (GameObject* i : destroyList)
	{
		gameObjects.remove(i);
		delete i;
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (GameObject* i : gameObjects)
	{
		i->Draw(cameraMatrix);
	}
}

void CS230::GameObjectManager::CollideTest()
{
	for (GameObject* obj_A : gameObjects)
	{
		if (obj_A != nullptr)
		{
			for (GameObject* obj_B : gameObjects)
			{
				if (obj_B != nullptr && obj_A != obj_B)
				{
					if (obj_A->CanCollideWith(obj_B->GetObjectType()))
					{
						if (obj_A->DoesCollideWith(obj_B))
						{
							Engine::GetLogger().LogEvent("Collision Detected: " + obj_A->GetObjectTypeName() + " and " + obj_B->GetObjectTypeName());
							obj_A->ResolveCollision(obj_B);
						}
					}
				}
			}
		}
	}
}

