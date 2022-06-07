/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/30/2022
-----------------------------------------------------------------*/
#include "TextureManager.h"
#include "Engine.h"
#include "Texture.h"

CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
    if (pathToTexture.count(filePath) == 0)  //filePath does not exist in our map
    {
        pathToTexture[filePath] = new Texture(filePath);
    }
    return pathToTexture[filePath];
}

void CS230::TextureManager::Unload()
{
    for (std::pair<std::filesystem::path, Texture*> i : pathToTexture)
    {
        delete i.second;
    }
    pathToTexture.clear();
    Engine::GetLogger().LogEvent("Clear Textures");
}