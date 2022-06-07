/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 4/05/2022
-----------------------------------------------------------------*/
#include "Input.h"
#include "Engine.h"

CS230::InputKey::InputKey(Keyboard button) : button(button) {}

bool CS230::InputKey::IsKeyDown() const
{
	return Engine::GetInput().IsKeyDown(button);
}

bool CS230::InputKey::IsKeyReleased() const
{
	return Engine::GetInput().IsKeyReleased(button);
}

CS230::Input::Input()
{
	//resize the keyDown and wasKeyDown vector to the correct size
	//keyDown and wasKeyDown will be used to maintain the state of the keys that we care about
	keyDown.assign(static_cast<unsigned int>(InputKey::Keyboard::Count), false);
	wasKeyDown.assign(static_cast<unsigned int>(InputKey::Keyboard::Count), false);
}

bool CS230::Input::IsKeyDown(InputKey::Keyboard key) const
{
	//used only by InputKey
	return keyDown[static_cast<int>(key)];
}
bool CS230::Input::IsKeyReleased(InputKey::Keyboard key) const
{
	//used only by InputKey
	if (keyDown[static_cast<int>(key)] == false && wasKeyDown[static_cast<int>(key)] == true)
	{
		return true;
	}
	return false;
}

void CS230::Input::SetKeyDown(InputKey::Keyboard key, bool value)
{
	keyDown[static_cast<int>(key)] = value;
}

void CS230::Input::Update()
{
	wasKeyDown = keyDown;
}