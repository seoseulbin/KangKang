/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode3.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 06/08/2022
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Mode3.h"
#include "Player.h"
#include "Background.h"
#include "Car.h"
#include "Fonts.h"
#include "Timer.h"
#include "Score.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "Hares.h"
#include "Coin.h"

#include <iostream>


Mode3::Mode3() : Reload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Escape), lives(3),
gameObjectManager(nullptr), playerPtr(nullptr), BGround(nullptr), timerPtr(nullptr), scorePtr(nullptr)
{
}

void Mode3::Load()
{
	gameObjectManager = new CS230::GameObjectManager();
	AddGSComponent(gameObjectManager);
	playerPtr = new Player({ 600, 0 });
	gameObjectManager->Add(new Car({ 30, 460 }, 1));
	gameObjectManager->Add(new Car({ 350, 460 }, 1));
	gameObjectManager->Add(new Car({ 850, 460 }, 1));
	gameObjectManager->Add(new Car({ 40, 215 }, 2));
	gameObjectManager->Add(new Car({ 490, 215 }, 2));
	gameObjectManager->Add(new Car({ 1000, 215 }, 2));
	gameObjectManager->Add(new Car({ 40, 705 }, 3));
	gameObjectManager->Add(new Car({ 1000, 705 }, 3));
	gameObjectManager->Add(new Car({ 20, 950 }, 5));
	gameObjectManager->Add(new Car({ 750, 950 }, 5));
	gameObjectManager->Add(new Car({ 5, 1150 }, 4));
	gameObjectManager->Add(new Car({ 580, 1150 }, 4));
	gameObjectManager->Add(new Car({ 950, 1150 }, 4));
	gameObjectManager->Add(new Car({ 1320, 1150 }, 4));
	gameObjectManager->Add(new Hares({ 0, 1395}, { 1440, 1395 }, playerPtr));
	gameObjectManager->Add(new Hares({ 1440, 1395 }, { 0, 1395 }, playerPtr));
	gameObjectManager->Add(new Hares({ 200, 1650 }, { 1200, 1650 }, playerPtr));
	gameObjectManager->Add(new Hares({ 1200, 1650 }, { 200, 1650 }, playerPtr));
	gameObjectManager->Add(new Coin({ 100, 1850 }, 1));
	gameObjectManager->Add(new Coin({ 410, 1850 }, 2));
	gameObjectManager->Add(new Coin({ 730, 1850 }, 3));
	gameObjectManager->Add(new Coin({ 1020, 1850 }, 2));
	gameObjectManager->Add(new Coin({ 1320, 1850 }, 1));
	gameObjectManager->Add(playerPtr);
	scorePtr = new Score({ 0, Fonts::Font1 });
	timerPtr = new Timer(60);

	AddGSComponent(new Background());
	AddGSComponent(scorePtr);
	AddGSComponent(timerPtr);

	BGround = GetGSComponent<Background>();
	BGround->Add("Assets/background3.png", 1 );

	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("You Lose !", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Press r to restart !", 0xFFFFFFFF, true);

	WinTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Congratulation! You win!!", 0xFFFFFFFF, true);
	FinalScoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture("Your score is : " + std::to_string(scorePtr->GetScore()), 0xFFFFFFFF, true);

	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);
	
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0 , 0.03 * Engine::GetWindow().GetSize().y }, { 0, 0.35 * Engine::GetWindow().GetSize().y } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0 ,0 }, { BGround->Size() - Engine::GetWindow().GetSize() } });
	cameraPtr->SetPosition(math::vec2{ 0, 0});

#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode3::Update(double dt)
{
	gameObjectManager->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(playerPtr->GetPosition());
	//std::cout <<"camera position : "<< -GetGSComponent<CS230::Camera>()->GetPosition().y << std::endl;
	//std::cout <<"Hero position : "<< playerPtr->GetPosition().y << std::endl;
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	scorePtr->Update(dt);
	timerPtr->Update(dt);

	if (timerPtr->hasEnded() == true)
	{
		lives -= 1;
		if (lives == 0)
		{
			playerPtr->SetIsReallyDead(true);
			if (playerPtr->GetIsReallyDead() == true)
			{
				if (Reload.IsKeyDown() == true)
				{
					lives = 3;
					Engine::GetGameStateManager().ReloadState();
				}
			}
			
		}
		/*else
		{
			Engine::GetGameStateManager().ReloadState();
		}*/
	}
	
#ifdef _DEBUG
	if (Reload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
}

void Mode3::Unload()
{
	ClearGSComponent();
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x2976bbFF);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	BGround->Draw(*cameraPtr);

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	timerPtr->Draw(math::ivec2{ winSize.x - 270, winSize.y - 10 });
	scorePtr = GetGSComponent<Score>();
	scorePtr->Draw(math::ivec2{ 10 , winSize.y - 5 });
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x - 830 , winSize.y - 80 }));

	if (playerPtr->GetIsReallyDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 - GameOverTexture.GetSize().y }));
	}

	if (playerPtr->GetEscape() == true)
	{
		WinTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - WinTexture.GetSize().x / 2, winSize.y / 2 }));
		FinalScoreTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - FinalScoreTexture.GetSize().x / 2, winSize.y / 2 - FinalScoreTexture.GetSize().y }));
	}
}

