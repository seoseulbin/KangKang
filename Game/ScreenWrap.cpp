#include "ScreenWrap.h"
#include "..\Engine\Engine.h"
#include "Screens.h"
#include "GameObjectTypes.h"
void ScreenWrap::Update(double)
{
	if (object.GetObjectType() == GameObjectType::Car)
	{
		if (object.GetPosition().x + (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) < 0)
		{
			object.SetPosition({ static_cast<double>(Engine::GetWindow().GetSize().x) + static_cast<double>((object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2)) ,  object.GetPosition().y });
		}
		else if (object.GetPosition().x - (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) > Engine::GetWindow().GetSize().x)
		{
			object.SetPosition({ -(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) ,  object.GetPosition().y });
		}
	}
	else
	{
		if (object.GetPosition().x + (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) < 0)
		{
			object.SetPosition({ static_cast<double>(Engine::GetWindow().GetSize().x) + static_cast<double>((object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2)) ,  object.GetPosition().y });
		}
		else if (object.GetPosition().x - (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) > Engine::GetWindow().GetSize().x)
		{
			object.SetPosition({ -(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) ,  object.GetPosition().y });
		}
		else if (object.GetPosition().y - object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y > Engine::GetWindow().GetSize().y)
		{
			object.SetPosition({ object.GetPosition().x,  -(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) });
		}
		else if (object.GetPosition().y + (object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) < 0)
		{
			object.SetPosition({ object.GetPosition().x,  static_cast<double>(Engine::GetWindow().GetSize().y) + static_cast<double>(object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2) });
		}
	}
}
