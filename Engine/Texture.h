/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.h
Project: CS230
Author: Seulbin Seo
Creation date: 05/03/2022
-----------------------------------------------------------------*/
#pragma once
#include <doodle/image.hpp>
#include "Vec2.h"
#include "TransformMatrix.h"

namespace CS230
{
	class Texture
	{
		friend class TextureManager;
		friend class SpriteFont;
	public:
		Texture() {}
		void Draw(math::TransformMatrix displayMatrix);
		void Draw(math::TransformMatrix displayMatrix, math::ivec2 texelPos, math::ivec2 frameSize);
		math::ivec2 GetSize();
		unsigned int GetPixel(math::ivec2 texel);

	private:
		Texture(const std::filesystem::path& filePath);
		Texture(doodle::Image&& doodleImage);
		doodle::Image image;
	};
}