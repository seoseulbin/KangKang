/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input_Doodle.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 4/05/2022
-----------------------------------------------------------------*/
#include <doodle/input.hpp>	
#include "Input.h"
#include "Engine.h"			// GetLogger, GetInput

CS230::InputKey::Keyboard DoodleKeyToCS230Key(doodle::KeyboardButtons button)
{
	if (button == doodle::KeyboardButtons::Enter)
	{
		return CS230::InputKey::Keyboard::Enter;
	}
	else if (button == doodle::KeyboardButtons::Escape)
	{
		return CS230::InputKey::Keyboard::Escape;
	}
	else if (button == doodle::KeyboardButtons::Space)
	{
		return CS230::InputKey::Keyboard::Space;
	}
	else if (button == doodle::KeyboardButtons::Left)
	{
		return CS230::InputKey::Keyboard::Left;
	}
	else if (button == doodle::KeyboardButtons::Right)
	{
		return CS230::InputKey::Keyboard::Right;
	}
	else if (button == doodle::KeyboardButtons::Up)
	{
		return CS230::InputKey::Keyboard::Up;
	}
	else if (button == doodle::KeyboardButtons::Down)
	{
		return CS230::InputKey::Keyboard::Down;
	}
	else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z)
	{
		//*offset : a value that is added to another base value.
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<CS230::InputKey::Keyboard>(static_cast<int>(CS230::InputKey::Keyboard::A) + offset);
	}
	else if (button == doodle::KeyboardButtons::Tilde)
	{
		return CS230::InputKey::Keyboard::Tilde;
	}
	return CS230::InputKey::Keyboard::None;
}

//include doodle/input.hpp

void on_key_pressed(doodle::KeyboardButtons doodleButton)
{
	CS230::InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != CS230::InputKey::Keyboard::None)
	{
		Engine::GetInput().SetKeyDown(button, true);
		Engine::GetLogger().LogDebug("on_key_pressed");
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton)
{
	CS230::InputKey::Keyboard button = DoodleKeyToCS230Key(doodleButton);
	if (button != CS230::InputKey::Keyboard::None)
	{
		Engine::GetInput().SetKeyDown(button, false);
		Engine::GetLogger().LogDebug("on_key_released");
	}
}