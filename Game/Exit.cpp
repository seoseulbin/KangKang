/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 5/23/2022
-----------------------------------------------------------------*/
#include "Exit.h"
#include "../Engine/Rect.h"
#include "../Engine/Engine.h"
#include "Screens.h"
#include "GameObjectTypes.h"
#include "../Engine/Collision.h"

Exit::Exit(math::irect2 rect) : GameObject(static_cast<math::vec2>( rect.point1))
{
	AddGOComponent(new CS230::RectCollision({ {0, 0}, rect.Size() }, this));
}

void Exit::ResolveCollision(GameObject* objectA)
{
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}
