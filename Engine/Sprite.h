/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 04/15/2022
-----------------------------------------------------------------*/
#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "Vec2.h"
#include "Component.h"

namespace math {
	class TransformMatrix;
}

namespace CS230 {
	class Texture;
	class Animation;
}

namespace CS230
{
	class GameObject;
	class Sprite : public Component
	{
	public:
		Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
		~Sprite();
		void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
		void Update(double dt) override;
		void Draw(math::TransformMatrix displayMatrix);
		void PlayAnimation(int anim);
		int GetCurrentAnim();
		bool IsAnimationDone();

		math::ivec2 GetHotSpot(int index);
		math::ivec2 GetFrameSize() const;

	private:
		math::ivec2 GetFrameTexel(int frameNum) const;
		Texture* texturePtr;
		int currFrame;
		math::ivec2 frameSize;
		std::vector<math::ivec2> frameTexel;
		std::vector<Animation*> animations;
		std::vector<math::ivec2> hotSpotList;
		
	};
}