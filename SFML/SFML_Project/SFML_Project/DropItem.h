#pragma once
#include "Util.h"
class DropItem
{
public:
	enum class ItemType { EXP, GOLD, HEALTH };
	ItemType type;
	void PickUp();
};

