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
#include "..\Engine\TransformMatrix.h"
#include "TreeStump.h"
#include "Fonts.h"
#include "Timer.h"
#include "Score.h"
#include "Gravity.h"
#include "Floor.h"

Mode3::Mode3() : Reload(CS230::InputKey::Keyboard::R), modeNext(CS230::InputKey::Keyboard::Escape), gameObjectManager(nullptr)
{
}

void Mode3::Load()
{
	
#ifdef _DEBUG
	
#endif
}

void Mode3::Update(double dt)
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
#endif
}

void Mode3::Unload()
{
	ClearGSComponent();
}

void Mode3::Draw()
{
	Engine::GetWindow().Clear(0x2976bbFF);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
}

