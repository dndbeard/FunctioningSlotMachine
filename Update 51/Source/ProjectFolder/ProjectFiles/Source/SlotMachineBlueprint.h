#pragma once
#include "Constants.h"
#include "Block.h"

class SlotMachineBlueprint {
public:
	static const int size = 12;
	Block blocks[size];

	SlotMachineBlueprint();
};