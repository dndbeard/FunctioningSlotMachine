#pragma once
#include "Constants.h"
#include "Block.h"
#include "Structure/IBlueprint.h"

class SlotMachineBlueprint {
public:
	static const int size = 12;		
	static const int occupiedSize = 3;
	static const int variantAmount = 4;
	Block* output;					
	Block* button;
	Block blocks[size];
	Block occupiedBlocks[occupiedSize];

	SlotMachineBlueprint();
	SlotMachineBlueprint(int variant);

	static SlotMachineBlueprint getBlueprint(int variant);
};