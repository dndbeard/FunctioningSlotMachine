#pragma once
#include "Constants.h"
#include "Block.h"

class SlotMachineBlueprint {
public:
	static const int size = 12;		// this structure consists of 12 blocks, excluding the origin block
	static const int blueprintAmount = 4;
	Block* output;					// this is where the rewards come out from
	Block* button;
	Block blocks[size];				// array that holds info about blocks inside structure

	SlotMachineBlueprint();
	SlotMachineBlueprint(int x);

	static SlotMachineBlueprint getBlueprint(int x);
};