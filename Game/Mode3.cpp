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

#include <iostream>


Mode3::Mode3() : Reload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Escape), 
gameObjectManager(nullptr), playerPtr(nullptr), BGround(nullptr)
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
	gameObjectManager->Add(new Car1({ 550, 1190 }, playerPtr));
	gameObjectManager->Add(new Car2({ 20, 1190 }));
	gameObjectManager->Add(new Car2({ 320, 1190 }));
	gameObjectManager->Add(new Car2({ 620, 1190 }));
	gameObjectManager->Add(new Car2({ 920, 1190 }));
	gameObjectManager->Add(playerPtr);

	AddGSComponent(new Background());

	BGround = GetGSComponent<Background>();
	BGround->Add("Assets/background3.png", 1 );


	
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0 , 0.03 * Engine::GetWindow().GetSize().y }, { 0, 0.35 * Engine::GetWindow().GetSize().y } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0 ,0 }, { BGround->Size() - Engine::GetWindow().GetSize() } });
	cameraPtr->SetPosition(math::vec2{ 0, 0});

#ifdef _DEBUG
	
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
	BGround->Draw(*cameraPtr);

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);
}

