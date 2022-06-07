/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/03/2022
-----------------------------------------------------------------*/
#include "MainMenu.h"
#include "..\Engine\Engine.h"
#include "Fonts.h"
#include "..\Engine\TransformMatrix.h"
#include "Screens.h"

MainMenu::MainMenu()
	: upKey(CS230::InputKey::Keyboard::Up),
	downKey(CS230::InputKey::Keyboard::Down),
	selectKey(CS230::InputKey::Keyboard::Enter), selectedIndex(0) {}

void MainMenu::Load() 
{
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) 
	{
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Mode1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update(double)
{
	if (upKey.IsKeyReleased() == true) 
	{
		if (selectedIndex <= 0) 
		{
			selectedIndex = 0;
			RenderOption(optionsData[selectedIndex], true);
		}
		if(selectedIndex > 0) 
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex--;
			RenderOption(optionsData[selectedIndex], true);
		}
	}

	if (downKey.IsKeyReleased() == true) 
	{
		if (selectedIndex >= 0 && selectedIndex < 3) 
		{
			RenderOption(optionsData[selectedIndex], false);
			selectedIndex++;
			RenderOption(optionsData[selectedIndex], true);
		}
		if (selectedIndex >= 3)
		{
			selectedIndex = 3;
			RenderOption(optionsData[selectedIndex], true);
		}
	}

	if (selectKey.IsKeyReleased() == true) 
	{
		switch (selectedIndex)
		{
		case 0:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode1));
			break;
		case 1:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode2));
			break;
		case 2:
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Mode3));
			break;
		case 3:
			Engine::GetGameStateManager().Shutdown();
			break;
		}
	}
}

void MainMenu::Unload() {}

void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x2976bbFF);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	title.Draw(
		math::TranslateMatrix{ math::ivec2{ winSize.x / 2 - title.GetSize().x, winSize.y /2 } } *math::ScaleMatrix({ 2, 2 })
	);
	for (int i = 0; i < static_cast<int>(Options::Count); i++) 
	{
	optionsData[i].texture.Draw(
		math::TranslateMatrix{ math::ivec2{ winSize.x / 2 - optionsData[i].texture.GetSize().x / 2, winSize.y / 2 - optionsData->texture.GetSize().y * 2 - optionsData->texture.GetSize().y * i}});
	}
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted)
{
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(
	data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}


MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = 
{
	{"Side Scroller", {0.5, 0.55}, {} },
	{"Space Shooter", {0.5, 0.45}, {} },
	{"Kang Kang", {0.5, 0.35}, {}},
	{"Quit", {0.5, 0.25}, {} }
};
