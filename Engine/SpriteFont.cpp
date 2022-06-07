/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SpriteFont.cpp
Project: CS230
Author: Kevin Wright, &Seulbin Seo
Creation date: 05/03/2022
-----------------------------------------------------------------*/
#include "doodle/drawing.hpp"	//set_tint_color
#include "Engine.h"
#include "SpriteFont.h"
#include "TransformMatrix.h"

CS230::SpriteFont::SpriteFont(const std::filesystem::path& fileName) : texture(fileName) 
{
	unsigned int white = 0xFFFFFFFF;
	unsigned int color = texture.GetPixel({ 0, 0 });
	if (color != white) 
	{
		Engine::GetLogger().LogError("Sprite font " + fileName.string() + " not setup correctly");
		return;
	}

	SetupCharRects();
}

void CS230::SpriteFont::SetupCharRects() 
{
	unsigned int testColor = texture.GetPixel({ 0, 0 });
	unsigned int nextColor = 0;

	int height = texture.GetSize().y;

	int xPos = 1;
	for (int index = 0; index < numOfChars; index++) 
	{
		nextColor = texture.GetPixel({ xPos, 0 });
		charTexels[index].point1 = { xPos, height };
		while ( nextColor == testColor ) 
		{
			xPos++;
			nextColor = texture.GetPixel({ xPos, 0 });
		}

		testColor = nextColor;

		charTexels[index].point2 = { xPos -1, 1};
	}
}

math::irect2& CS230::SpriteFont::GetCharRect(char c) 
{
	if (c >= ' ' && c <= 'z') 
	{
		return charTexels[c - ' '];
	} 
	else 
	{
		Engine::GetLogger().LogError("character '" + std::to_string(c) + "' not found in spriteFont");
		return charTexels[0];
	}
}

math::ivec2 CS230::SpriteFont::MeasureText(std::string text) 
{
	math::ivec2 size = { 0,0 };
	for (char c : text) 
	{
		size.x += charTexels[static_cast<int>(c - ' ')].Size().x;
	}
	size.y = charTexels[0].Size().y;
	return size;
}

CS230::Texture CS230::SpriteFont::DrawTextToTexture(std::string text, unsigned int color, bool drawShadow) 
{

	math::ivec2 textSize = MeasureText(text);
	if (drawShadow == true)
	{
		textSize += math::ivec2{3, 3};
	}

	doodle::begin_drawing_to_image(textSize.x, textSize.y, true);  

	math::TransformMatrix matrix;
	if (drawShadow == true) 
	{

		doodle::set_tint_color(doodle::HexColor(0x000000FF));   //black
		for (char c : text) 
		{
			DrawChar(matrix, c);
		}
		matrix = math::TranslateMatrix(math::ivec2{ 3,3 });
	}

	doodle::set_tint_color(doodle::HexColor(color));
	for (char c : text) 
	{
		DrawChar(matrix, c);
	}
	doodle::set_tint_color(doodle::HexColor(0xFFFFFFFF));
	return CS230::Texture(doodle::end_drawing_to_image());
}

void CS230::SpriteFont::DrawChar(math::TransformMatrix& matrix, char c) 
{
	math::irect2& displayRect = GetCharRect(c);
	math::ivec2 topLeftTexel = { displayRect.point1.x, displayRect.point2.y };
	if (c != ' ') 
	{
		texture.Draw(matrix, topLeftTexel, displayRect.Size());
	}
	matrix *= math::TranslateMatrix(math::ivec2{ displayRect.Size().x, 0 });
}