/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShowCollision.cpp
Project: CS230
Author: Seulbin.seo
Creation date: 05/24/2021
-----------------------------------------------------------------*/

#include "ShowCollision.h"

ShowCollision::ShowCollision(CS230::InputKey::Keyboard keyToUse)
	: showCollisionKey(keyToUse), enabled(false)
{
	keyToUse = CS230::InputKey::Keyboard::Tilde;
}

void ShowCollision::Update(double)
{
	if (showCollisionKey.IsKeyReleased() == true) 
	{
		enabled = !enabled;
	}
}

bool ShowCollision::IsEnabled()
{
	if(this != nullptr)
	{
		return enabled;
	}
	return false;
}
