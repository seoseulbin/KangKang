/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/15/2022
-----------------------------------------------------------------*/

#include "Collision.h"
#include "TransformMatrix.h"
#include "doodle/drawing.hpp"
#include "GameObject.h"
#include "Rect.h"

#include <iostream>

void CS230::RectCollision::Draw(math::TransformMatrix cameraMatrix)
{
	doodle::no_fill();
	doodle::set_outline_width(2);
	doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
	doodle::push_settings();
	math::rect2 displayRect = GetWorldCoorRect();
	doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
	doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
	doodle::pop_settings();
}

math::rect2 CS230::RectCollision::GetWorldCoorRect()
{
	return { objectPtr->GetMatrix() * static_cast<math::vec2>(rect.point1),
	objectPtr->GetMatrix() * static_cast<math::vec2>(rect.point2) };
}

bool CS230::RectCollision::DoesCollideWith(GameObject* objectB)
{
	if (GetWorldCoorRect().Left() < objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Right()
		&& GetWorldCoorRect().Top() > objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Bottom()
		&& GetWorldCoorRect().Right() > objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Left()
		&& GetWorldCoorRect().Bottom() < objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Top())
	{
		return true;
	}
	return false;
}

bool CS230::RectCollision::DoesCollideWith(math::vec2 point)
{
	if (GetWorldCoorRect().Left() <= point.x && point.x <= GetWorldCoorRect().Right())
	{
		if (GetWorldCoorRect().Bottom() <= point.y && point.y <= GetWorldCoorRect().Top())
		{
			return true;
		}
	}
	return false;
}

void CS230::CircleCollision::Draw(math::TransformMatrix cameraMatrix)
{
	doodle::no_fill();
	doodle::set_outline_width(2);
	doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
	doodle::push_settings();
	doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
	doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
	doodle::pop_settings();
}

double CS230::CircleCollision::GetRadius()
{
	return objectPtr->GetScale().x * radius;
}

bool CS230::CircleCollision::DoesCollideWith(GameObject* objectB)
{
	double objDis_x = objectPtr->GetPosition().x - objectB->GetPosition().x;
	double objDis_y = objectPtr->GetPosition().y - objectB->GetPosition().y;
	double objB_r = objectB->GetGOComponent<CS230::CircleCollision>()->GetRadius();
	double plus_r = GetRadius() + objB_r;

	if ((objDis_x * objDis_x) + (objDis_y * objDis_y) < (plus_r * plus_r))
	{
		return true;
	}
	return false;
}

bool CS230::CircleCollision::DoesCollideWith(math::vec2 point)
{
	if ((objectPtr->GetPosition().x - point.x) * (objectPtr->GetPosition().x - point.x) + (objectPtr->GetPosition().y - point.y) * (objectPtr->GetPosition().y - point.y) < GetRadius() * GetRadius())
	{
		return true;
	}
	return false;
}
