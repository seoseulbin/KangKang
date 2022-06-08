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
#include "Car1.h"
#include "Car2.h"
#include "Car3.h"
#include "Fonts.h"
#include "Timer.h"
#include "Score.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "Hares.h"

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
	gameObjectManager->Add(new Car1({ 30, 460 }, playerPtr));
	gameObjectManager->Add(new Car1({ 350, 460 }, playerPtr));
	gameObjectManager->Add(new Car1({ 850, 460 }, playerPtr));
	gameObjectManager->Add(new Car2({ 40, 215 }));
	gameObjectManager->Add(new Car2({ 490, 215 }));
	gameObjectManager->Add(new Car2({ 1000, 215 }));
	gameObjectManager->Add(new Car3({ 40, 705 }));
	gameObjectManager->Add(new Car3({ 1000, 705 }));
	gameObjectManager->Add(new Car1({ 5, 950 }, playerPtr));
	gameObjectManager->Add(new Car1({ 550, 950 }, playerPtr));
	gameObjectManager->Add(new Car2({ 10, 1150 }));
	gameObjectManager->Add(new Car2({ 360, 1150 }));
	gameObjectManager->Add(new Car2({ 850, 1150 }));
	gameObjectManager->Add(new Car2({ 1150, 1150 }));
	gameObjectManager->Add(new Hares({ 0, 1395}, { 1440, 1395 }, playerPtr));
	gameObjectManager->Add(new Hares({ 1440, 1395 }, { 0, 1395 }, playerPtr));
	gameObjectManager->Add(new Hares({ 200, 1650 }, { 1200, 1650 }, playerPtr));
	gameObjectManager->Add(new Hares({ 1200, 1650 }, { 200, 1650 }, playerPtr));
	gameObjectManager->Add(playerPtr);
	scorePtr = new Score({ 0, Fonts::Font1 });
	timerPtr = new Timer(60);

	AddGSComponent(new Background());
	AddGSComponent(scorePtr);
	AddGSComponent(timerPtr);

	BGround = GetGSComponent<Background>();
	BGround->Add("Assets/background3.png", 1 );

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

	if (timerPtr->hasEnded() == true || playerPtr->IsDead() == true)
	{
		lives--;
		if (lives == 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
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
}

