#include "ShowCollision.h"

ShowCollision::ShowCollision(CS230::InputKey::Keyboard keyToUse)
	: showCollisionKey(keyToUse), enabled(false)
{
	keyToUse = CS230::InputKey::Keyboard::Tilde;
}

void ShowCollision::Update(double)
{
	if (showCollisionKey.IsKeyReleased() == true) 
	{
		enabled = !enabled;
	}
}

bool ShowCollision::IsEnabled()
{
	if(this != nullptr)
	{
		return enabled;
	}
	return false;
}
