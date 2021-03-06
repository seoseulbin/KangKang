/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/30/2022
-----------------------------------------------------------------*/
#include "GameStateManager.h"
#include "Engine.h"
#include "GameState.h"  //Forward Declaration
#include "GameObjectManager.h"

CS230::GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr) 
{
	state = State::START;
}

void CS230::GameStateManager::AddGameState(GameState& gameState)
{
	gameStates.push_back(&gameState);
}

void CS230::GameStateManager::Update(double dt)
{
	switch (state)
	{
	case State::START:
		if (gameStates.empty())
		{
			Engine::GetLogger().LogError("No next state");
			state = State::SHUTDOWN;
		}
		else
		{
			state = State::LOAD;
			nextGameState = gameStates[0];
		}
		break;
	case State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete ");
		state = State::UPDATE;
		break;
	case State::UPDATE:
		if (currGameState != nextGameState)
		{
			state = State::UNLOAD;
		}
		else
		{
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			currGameState->Update(dt);
			if (GetGSComponent<CS230::GameObjectManager>() != nullptr)
			{

			currGameState->GetGSComponent<CS230::GameObjectManager>()->CollideTest();
			}
			currGameState->Draw();
		}
		break;
	case State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		if (nextGameState != currGameState) 
		{
			Engine::GetTextureManager().Unload();
		}
		currGameState->Unload();
		if (nextGameState == nullptr)
		{
			state = State::SHUTDOWN;
		}
		else
		{
			state = State::LOAD;
		}
		break;
	case State::SHUTDOWN:
		state = State::EXIT;
		break;
	case State::EXIT:
		break;
	}
}

void CS230::GameStateManager::SetNextState(int initState)
{
	nextGameState = gameStates[initState];
}

void CS230::GameStateManager::Shutdown()
{
	nextGameState = nullptr;
}

void CS230::GameStateManager::ReloadState()
{
	state = State::UNLOAD;
}