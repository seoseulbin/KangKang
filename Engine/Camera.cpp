/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: CS230
Author: Seulbin Seo
Creation date: 04/25/2022
-----------------------------------------------------------------*/
#include "Camera.h"
#include "Engine.h"
#include "../Game/Background.h"
CS230::Camera::Camera(math::rect2 movableRange) : movableRange(movableRange) {}

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
	if (followObjPos.x < position.x + movableRange.Left())
	{
		position.x = followObjPos.x - movableRange.Left();
	}
	if (followObjPos.x > position.x + movableRange.Right())
	{
		position.x = followObjPos.x - movableRange.Right();
	}

	if (followObjPos.y < position.y - movableRange.Bottom())
	{
		position.y = followObjPos.y + movableRange.Bottom();
	}
	if (followObjPos.y > position.y + movableRange.Top())
	{
		position.y= followObjPos.y - movableRange.Top();
	}
	//if (followObjPos.y < position.y - movableRange.Top()*2)
	//{
	//	position.y = followObjPos.y - movableRange.Top()*2;
	//}
	//if (followObjPos.y < position.y + movableRange.Bottom())
	//{
	//	position.y = followObjPos.y +movableRange.Bottom();
	//}

	if (position.x < extent.Left())
	{
	
		position.x = extent.Left();
	}
	else if (position.x > extent.Right())
	{
		position.x = extent.Right();
	}

	if (position.y > extent.Top())
	{
		position.y =extent.Top();
	}

	/*if (-position.y < extent.Bottom()) 
	{
		position.y = 0;
	}
	if (-position.y > Engine::Instance().GetGSComponent<Background>()->Size().y + extent.Top() +200)
	{
		position.y = Engine::Instance().GetGSComponent<Background>()->Size().y + extent.Top() +200;
	}*/
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix(-position);
}






