/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/25/2022
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"
#include "../Engine/Texture.h"

Splash::Splash() :texturePtr(nullptr) {}

void Splash::Load()
{
	texturePtr = Engine::GetTextureManager().Load("assets/Digipen_BLACK_1024px.png");
}

void Splash::Update(double dt)
{
	m_dt += dt;
	if (m_dt > 3) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}

void Splash::Unload() {}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xFFFFFFFF);
	texturePtr->Draw(math::TranslateMatrix
		{
			Engine::GetWindow().GetSize() / 2.f - texturePtr->GetSize() / 2.f
		});
}
