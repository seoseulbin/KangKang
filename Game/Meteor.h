/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.h
Project: CS230
Author: Seulbin Seo
Creation date: 4/30/2022
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Engine.h"
#include "GameObjectTypes.h"

class Meteor : public CS230::GameObject 
{
public:
	Meteor();
	Meteor(Meteor& original);
	void Update(double dt) override;
	GameObjectType GetObjectType()override;
	std::string GetObjectTypeName()override;
	void ResolveCollision(GameObject* objectB) override;

private:
	static constexpr double PI = 3.141592653589793;
	int health;
	int size;

};
