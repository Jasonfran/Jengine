#pragma once
#include "Component.h"

class PlayerComponent : public Component {
public:
	std::string playerName = "Jason";
	PlayerComponent() {}
};