/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/15/2022
-----------------------------------------------------------------*/
#include "Engine.h"
#include <time.h>   

Engine::Engine() : frameCount(0), lastTick(std::chrono::system_clock::now()),
////initalize the logger
#ifdef _DEBUG		
//if Debug
logger(CS230::Logger::Severity::Debug, true, lastTick)
#else 		
//if Release
logger(CS230::Logger::Severity::Event, false, lastTick)
#endif
{}

Engine::~Engine() {}

void Engine::AddSpriteFont(const std::filesystem::path& fileName)
{
	fonts.push_back({ CS230::SpriteFont(fileName)});
}

void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	time_t seed = time(NULL);
	srand(static_cast<unsigned int>(seed));
	logger.LogEvent("Seed = " + std::to_string(seed));
	fpsCalcTime = lastTick;
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update()

{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();
	if (dt >= 1 / Engine::Target_FPS)
	{
		logger.LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
		++frameCount;
		if (frameCount > Engine::FPS_IntervalFrameCount)
		{
			double averageFrameRate = frameCount / std::chrono::duration<double>(now - fpsCalcTime).count();
			Engine::GetLogger().LogEvent(std::to_string(averageFrameRate));
			frameCount = 0;
			fpsCalcTime = now;
		}
		lastTick = now;
	}
}

bool Engine::HasGameEnded()
{
	return GetGameStateManager().HasGameEnded();
}

