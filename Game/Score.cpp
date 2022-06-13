/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project: CS230
Author: Seulbin Seo
Creation date: 5/25/2022
-----------------------------------------------------------------*/
#include "Score.h"
#include "Fonts.h"
#include "../Engine/Engine.h"

Score::Score(int startingScore, Fonts fontToUse)
	:score(startingScore), fontToUse(fontToUse)
{
	RenderText();
}

void Score::AddScore(int newPoints)
{
	score += newPoints;
}

void Score::Draw(math::ivec2 location)
{
	scoreTexture.Draw(math::TranslateMatrix{ math::ivec2{location.x,location.y - scoreTexture.GetSize().y - 5 } });
	RenderText();
}

void Score::RenderText()
{
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	switch (fontToUse)
	{
	case Fonts::Font1:
		scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
		break;
	case Fonts::Font2:
		scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
		break;
	default:
		break;
	}
}