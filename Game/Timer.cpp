/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.h
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
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
		if (timer < 0)
		{
			timeStop = true;
		}
	}
	
	if (timeStop == true)
	{
		timer = 0;
	}


		std::string timetexture = "Time: " + std::to_string(static_cast<int>(timer));
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timetexture, 0xFFFFFFFF, true);
	
}

void Timer::Draw(math::ivec2 location)
{
	timeTexture.Draw(math::TranslateMatrix{ math::ivec2{location.x,location.y - timeTexture.GetSize().y}});
}

bool Timer::hasEnded()
{
	if (timer <= 0)
	{
		return true;
	}
		return false;
}
