/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 05//2022
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Mode1.h"
#include "..\Engine\TransformMatrix.h"
#include "Hero.h"
#include "Ball.h"
#include "Bunny.h"
#include "TreeStump.h"
#include "Fonts.h"
#include "Timer.h"
#include "Score.h"
#include "Gravity.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "Floor.h"
#include "Exit.h"
#include "GameParticles.h"

Mode1::Mode1() : Reload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Escape), lives(3),
heroPtr(nullptr), timerPtr(nullptr), scorePtr(nullptr), BackGround(nullptr), gameObjectManager(nullptr)
{
}

void Mode1::Load()
{
	gameObjectManager = new CS230::GameObjectManager();
	AddGSComponent(gameObjectManager);
	AddGSComponent(new Gravity(1000.0));
	gameObjectManager->Add(new Ball({ 600, Mode1::floor }));
	gameObjectManager->Add(new Ball({ 2700, Mode1::floor }));
	gameObjectManager->Add(new Ball({ 4800, Mode1::floor }));
	gameObjectManager->Add(new TreeStump({ 300, Mode1::floor }, 3));
	gameObjectManager->Add(new TreeStump({ 1200, Mode1::floor }, 2));
	gameObjectManager->Add(new TreeStump({ 2200, Mode1::floor }, 1));
	gameObjectManager->Add(new TreeStump({ 2800, Mode1::floor }, 5));
	gameObjectManager->Add(new TreeStump({ 5100, Mode1::floor }, 3));
	gameObjectManager->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Mode1::floor)} }));
	gameObjectManager->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Mode1::floor)} }));
	gameObjectManager->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Mode1::floor)} }));
	gameObjectManager->Add(new Exit({ {5550, static_cast<int>(Mode1::floor)}, {5760, 683} }));
	heroPtr = new Hero({ 100, Mode1::floor - 1 });
	gameObjectManager->Add(new Bunny({ 1000, floor }, { 674, 1132 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 2000, floor }, { 1635, 2135 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3200, floor }, { 2860, 4250 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3800, floor }, { 2860, 4250 }, heroPtr));
	scorePtr = new Score({ 0, Fonts::Font1 });
	timerPtr = new Timer(60);

	gameObjectManager->Add(heroPtr);
	AddGSComponent(new SmokeEmitter());
	AddGSComponent(new Background());
	AddGSComponent(scorePtr);
	AddGSComponent(timerPtr);

	BackGround = GetGSComponent<Background>();

	BackGround->Add("Assets/clouds.png", 4);
	BackGround->Add("Assets/Mountains.png", 2);
	BackGround->Add("Assets/foreground.png", 1);

	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);

	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0.7 * Engine::GetWindow().GetSize().y } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0,0 }, { BackGround->Size() - Engine::GetWindow().GetSize() } });
	cameraPtr->SetPosition(math::vec2{ 0, 0 });

#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
}

void Mode1::Update(double dt)
{
	gameObjectManager->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	scorePtr->Update(dt);
	timerPtr->Update(dt);

	if (timerPtr->hasEnded() == true || heroPtr->IsDead() == true)
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

void Mode1::Unload()
{
	ClearGSComponent();
}

void Mode1::Draw()
{
	Engine::GetWindow().Clear(0x2976bbFF);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	BackGround->Draw(*cameraPtr);

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	timerPtr->Draw(math::ivec2{ winSize.x - 270, winSize.y - 10 });
	scorePtr = GetGSComponent<Score>();
	scorePtr->Draw(math::ivec2{ 10 , winSize.y - 5 });
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x - 830 , winSize.y - 80 }));
}

