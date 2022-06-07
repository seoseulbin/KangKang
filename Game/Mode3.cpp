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

Mode3::Mode3() : Reload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Escape), gameObjectManager(nullptr),
playerPtr(nullptr), BackGround(nullptr)
{
}

void Mode3::Load()
{
	gameObjectManager = new CS230::GameObjectManager();
	AddGSComponent(gameObjectManager);
	playerPtr = new Player({ 350, 200 });
	gameObjectManager->Add(playerPtr);

	BackGround = GetGSComponent<Background>();
	BackGround->Add("Assets/background3.png", 1);

	CS230::Camera* cameraPtr = new CS230::Camera({ { 0, 0.15 * Engine::GetWindow().GetSize().y }, { 0, 0.35 * Engine::GetWindow().GetSize().y } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0,0 }, { BackGround->Size() - Engine::GetWindow().GetSize() } });
	cameraPtr->SetPosition(math::vec2{ 0, 0 });

#ifdef _DEBUG
	
#endif
}

void Mode3::Update(double dt)
{
	gameObjectManager->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(playerPtr->GetPosition());
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	
#ifdef _DEBUG
	if (Reload.IsKeyReleased() == true) 
	{
		Engine::GetGameStateManager().ReloadState();
	}
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
	BackGround->Draw(*cameraPtr);

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);
}

