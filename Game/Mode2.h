/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Mode2.h
Project: CS230
Author: Seulbin Seo
Creation date: 05/03/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Ship.h"
#include "..\Engine\GameObjectManager.h"
#include "EnemyShip.h"

class Score;

class Mode2 : public CS230::GameState 
{
public:
	Mode2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "Mode2"; }
private:
	//int score;
	Ship* shipPtr;
	Score* scorePtr;
	EnemyShip* enemyShipPtr;
	CS230::Texture scoreTexture;
	CS230::Texture GameOverTexture;
	CS230::Texture RestartTexture;
	CS230::InputKey modeNext;
	CS230::InputKey Reload;
	CS230::GameObjectManager* gameObjectManager;
};