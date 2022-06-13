/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Main.cpp
Project: CS230 final project
Author: Seulbin Seo & Junsung Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include <stdexcept>	//std::exception
#include <iostream>		//std::cerr
#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/MainMenu.h"
#include "Game/Mode1.h"
#include "Game/Mode2.h"
#include "Game/Mode3.h"
#include "Game/Screens.h"


int main(void)
{
	try
	{
		Engine& engine = Engine::Instance();
		engine.Init("Final Project - Seulbin Seo & junsung Park");
		Splash splash;
		MainMenu mainmenu;
		Mode1 mode1;
		Mode2 mode2;
		Mode3 mode3;

		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainmenu);
		engine.GetGameStateManager().AddGameState(mode1);
		engine.GetGameStateManager().AddGameState(mode2);
		engine.GetGameStateManager().AddGameState(mode3);

		engine.AddSpriteFont("assets/font.png");
		engine.AddSpriteFont("assets/font2.png");

		while (engine.HasGameEnded() == false)
		{
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return -1;
	}
}