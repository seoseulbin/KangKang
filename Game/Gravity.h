/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gravity.h
Project: CS230
Author: Seulbin Seo
Creation date: 05/09/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Component.h" 

class Gravity : public CS230::Component {
public:
    Gravity(double value) : gravity(value) {}
    double GetValue() { return gravity; }
private:
    double gravity;
};