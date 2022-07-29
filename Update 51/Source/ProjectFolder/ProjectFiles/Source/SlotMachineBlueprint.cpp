#include "GameAPI.h"
#include "Constants.cpp"
#include "Block.h"


class SlotMachineBlueprint {
public:
	static const int size = 12;
	Block blocks[size];

	SlotMachineBlueprint() {
		blocks[0] = Block(0, 0, 1, FrameBlockID);
		blocks[1] = Block(0, 0, 2, FrameBlockID);
		blocks[2] = Block(0, 0, 3, SlotBarBlockID);
		blocks[3] = Block(0, 0, 4, FrameBlockID);

		blocks[4] = Block(1, 0, 1, FrameBlockID);
		blocks[5] = Block(1, 0, 2, SlotButtonBlockID);
		blocks[6] = Block(1, 0, 3, SlotBarBlockID);
		blocks[7] = Block(1, 0, 4, FrameBlockID);

		blocks[8] = Block(-1, 0, 1, FrameBlockID);
		blocks[9] = Block(-1, 0, 2, FrameBlockID);
		blocks[10] = Block(-1, 0, 3, SlotBarBlockID);
		blocks[11] = Block(-1, 0, 4, FrameBlockID);
	};

	

	

};