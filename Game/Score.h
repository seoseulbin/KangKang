/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.h
Project: CS230
Author: Seulbin Seo
Creation date: 5/09/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

enum class Fonts;

class Score : public CS230::Component {
public:
    Score(int startingScore, Fonts fontToUse);
    void AddScore(int newPoints);
    void Draw(math::ivec2 location);
    unsigned int GetScore() { return score; }
    void SetScore(unsigned int finalScore) { score = finalScore; }
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int score;
    CS230::Texture scoreTexture;
};