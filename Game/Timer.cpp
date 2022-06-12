/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.h
Project: CS230
Author: Seulbin Seo
Creation date: 5/09/2022
-----------------------------------------------------------------*/\
#include "Timer.h"
#include "../Engine/Engine.h"
#include "Fonts.h"

Timer::Timer(int time) : timer(time)
{
	timeStop = false;
}

void Timer::Update(double dt)
{
	if (timeStop == false)
	{
		timer -= dt;
	}
	else if (timeStop == true)
	{
		timer = 60;
	}

	if (static_cast<int>(timer))
	{
		std::string timetexture = "Time: " + std::to_string(static_cast<int>(timer + 1));
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timetexture, 0xFFFFFFFF, true);
	}
}

void Timer::Draw(math::ivec2 location)
{
	timeTexture.Draw(math::TranslateMatrix{ math::ivec2{location.x,location.y - timeTexture.GetSize().y}});
}

bool Timer::hasEnded()
{
	if (timer < 0)
	{
		return true;
	}
		return false;
}
