/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/15/2022
-----------------------------------------------------------------*/
#include "Background.h"
#include "../Engine/Camera.h"
#include "../Engine/TransformMatrix.h"
#include "../Engine/Engine.h"

void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath) , level });
}

math::ivec2 Background::Size()
{
	return math::ivec2(backgrounds.back().texturePtr->GetSize());
}

void Background::Draw(CS230::Camera& camera)
{
	for (ParallaxInfo& i : backgrounds)
	{
		i.texturePtr->Draw(math::TranslateMatrix::TranslateMatrix
		(
			math::vec2{ -camera.GetPosition().x / i.level, camera.GetPosition().y }
		));
	}
}
