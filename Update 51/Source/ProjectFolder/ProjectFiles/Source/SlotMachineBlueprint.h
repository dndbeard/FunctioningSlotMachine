#pragma once
#include "Constants.h"
#include "Block.h"
#include "Structure/IBlueprint.h"

class SlotMachineBlueprint {
public:
	static const int size = 12;		
	static const int blueprintAmount = 4;
	Block* output;					
	Block* button;
	Block blocks[size];				

	SlotMachineBlueprint();
	SlotMachineBlueprint(int x);

	static SlotMachineBlueprint getBlueprint(int x);
};