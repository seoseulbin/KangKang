/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.h
Project: CS230
Author: Seulbin Seo
Creation date: 5/09/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

class Timer : public CS230::Component {
public:
    Timer(int time);
    void Update(double dt) override;
    void Draw(math::ivec2 location);
    bool hasEnded();
    bool GetTimeStop() { return timeStop; }
    void SetTimeStop(bool timestop) { timestop = timeStop; }
private:
    double timer;
    bool timeStop;
    CS230::Texture timeTexture;
};