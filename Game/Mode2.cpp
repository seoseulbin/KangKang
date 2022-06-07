/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode2.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05/18/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Mode2.h"
#include "Ship.h"
#include "Meteor.h"
#include "Fonts.h"
#include "Screens.h"
#include "../Engine/ShowCollision.h"
#include "Score.h"
#include "GameParticles.h"

Mode2::Mode2() : modeNext(CS230::InputKey::Keyboard::Escape), Reload(CS230::InputKey::Keyboard::R),
gameObjectManager(nullptr), shipPtr(nullptr), scorePtr(nullptr), enemyShipPtr(nullptr) {}

void Mode2::Load()
{
	gameObjectManager = new CS230::GameObjectManager();
	AddGSComponent(gameObjectManager);
	shipPtr = new Ship({ Engine::GetWindow().GetSize() / 2.0 });
	gameObjectManager->Add(shipPtr);

	enemyShipPtr = new EnemyShip(shipPtr);
	gameObjectManager->Add(enemyShipPtr);

	scorePtr = new Score({ 0, Fonts::Font2 });
	AddGSComponent(scorePtr);

	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());

	AddGSComponent(new HitEmitter());
	AddGSComponent(new MeteorBitEmitter());

	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);
	
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode2::Update(double dt)
{
	gameObjectManager->Update(dt);
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (Reload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
	GetGSComponent<ShowCollision>()->Update(dt);

	scorePtr->Update(dt);
#else
	if (shipPtr->IsDead() == true)
	{
		if (Reload.IsKeyReleased() == true)
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
#endif // DEBUG
}

void Mode2::Unload() 
{
	ClearGSComponent();
	shipPtr = nullptr;
}

void Mode2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	math::TransformMatrix cameraMatrix;
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	scorePtr->Draw(math::ivec2{ 10, winSize.y});
	if (shipPtr->IsDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 - GameOverTexture.GetSize().y}));
	}
}