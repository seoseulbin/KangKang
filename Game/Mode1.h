/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode1.h
Project: CS230
Author: Seulbin Seo
Creation date: 04/15/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "..\Engine\Camera.h"
#include "Background.h"
#include "..\Engine\GameObjectManager.h"

namespace CS230 
{
	class Camera; //forward declare
}

class Hero;
class Score;
class Timer;
class Mode1 : public CS230::GameState
{
public:
	static constexpr double floor = 126.0f;
	static constexpr double gravity = 1000;

	Mode1();
	void        Load() override;
	void        Update( double dt) override;
	void        Unload() override;
	void        Draw() override;

	std::string GetName() override { return "Mode1"; }
private:
	int lives;
	CS230::Texture scoreTexture;
	CS230::Texture livesTexture;
	CS230::Texture timerTexture;
	
	Background* BackGround;
	CS230::InputKey Reload;
	CS230::InputKey modeNext;
	CS230::GameObjectManager* gameObjectManager;
	Hero* heroPtr;
	Score* scorePtr;
	Timer* timerPtr;
};