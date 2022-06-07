/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/23/2022
-----------------------------------------------------------------*/
#include "Floor.h"
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"

Floor::Floor(math::irect2 rect) : GameObject(static_cast<math::vec2>(math::ivec2{ rect.point1.x, rect.point1.y }))
{
	AddGOComponent(new CS230::RectCollision({ {0, 0}, rect.Size() }, this));
}