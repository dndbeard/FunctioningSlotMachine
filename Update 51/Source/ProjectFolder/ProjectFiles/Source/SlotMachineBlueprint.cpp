#include "SlotMachineBlueprint.h"

SlotMachineBlueprint::SlotMachineBlueprint() {
	blocks[0] = Block(0, 0, 1, FrameBlockID);
	blocks[1] = Block(0, 0, 2, FrameBlockID);
	blocks[2] = Block(0, 0, 3, SlotBarBlockID);
	blocks[3] = Block(0, 0, 4, FrameBlockID);

	blocks[4] = Block(1, 0, 1, FrameBlockID);
	blocks[5] = Block(1, 0, 2, FrameBlockID);
	blocks[6] = Block(1, 0, 3, SlotBarBlockID);
	blocks[7] = Block(1, 0, 4, FrameBlockID);

	blocks[8] = Block(-1, 0, 1, FrameBlockID);
	blocks[9] = Block(-1, 0, 2, SlotButtonBlockID);
	blocks[10] = Block(-1, 0, 3, SlotBarBlockID);
	blocks[11] = Block(-1, 0, 4, FrameBlockID);

	output = &blocks[1]; // this is where the rewards come out from
}

SlotMachineBlueprint::SlotMachineBlueprint(int x) {
	switch (x) { // Direction THE MACHINE is facing
	case 1: // north
		blocks[0] = Block(0, 0, 1, FrameBlockID);
		blocks[1] = Block(0, 0, 2, FrameBlockID);
		blocks[2] = Block(0, 0, 3, SlotBarBlockID);
		blocks[3] = Block(0, 0, 4, FrameBlockID);

		blocks[4] = Block(1, 0, 1, FrameBlockID);
		blocks[5] = Block(1, 0, 2, FrameBlockID);
		blocks[6] = Block(1, 0, 3, SlotBarBlockID);
		blocks[7] = Block(1, 0, 4, FrameBlockID);

		blocks[8] = Block(-1, 0, 1, FrameBlockID);
		blocks[9] = Block(-1, 0, 2, SlotButtonBlockID);
		blocks[10] = Block(-1, 0, 3, SlotBarBlockID);
		blocks[11] = Block(-1, 0, 4, FrameBlockID);

		output = &blocks[1]; // this is where the rewards come out from
		break;
	case 2: // south
		blocks[0] = Block(0, 0, 1, FrameBlockID);
		blocks[1] = Block(0, 0, 2, FrameBlockID);
		blocks[2] = Block(0, 0, 3, SlotBarBlockID);
		blocks[3] = Block(0, 0, 4, FrameBlockID);

		blocks[4] = Block(-1, 0, 1, FrameBlockID);
		blocks[5] = Block(-1, 0, 2, FrameBlockID);
		blocks[6] = Block(-1, 0, 3, SlotBarBlockID);
		blocks[7] = Block(-1, 0, 4, FrameBlockID);

		blocks[8] = Block(1, 0, 1, FrameBlockID);
		blocks[9] = Block(1, 0, 2, SlotButtonBlockID);
		blocks[10] = Block(1, 0, 3, SlotBarBlockID);
		blocks[11] = Block(1, 0, 4, FrameBlockID);

		output = &blocks[1]; // this is where the rewards come out from	default:
		break;
	case 3: // west
		blocks[0] = Block(0, 0, 1, FrameBlockID);
		blocks[1] = Block(0, 0, 2, FrameBlockID);
		blocks[2] = Block(0, 0, 3, SlotBarBlockID);
		blocks[3] = Block(0, 0, 4, FrameBlockID);

		blocks[4] = Block(0, 1, 1, FrameBlockID);
		blocks[5] = Block(0, 1, 2, FrameBlockID);
		blocks[6] = Block(0, 1, 3, SlotBarBlockID);
		blocks[7] = Block(0, 1, 4, FrameBlockID);

		blocks[8] = Block(0, -1, 1, FrameBlockID);
		blocks[9] = Block(0, -1, 2, SlotButtonBlockID);
		blocks[10] = Block(0, -1, 3, SlotBarBlockID);
		blocks[11] = Block(0, -1, 4, FrameBlockID);

		output = &blocks[1]; // this is where the rewards come out from
		break;
	case 4: // east
		blocks[0] = Block(0, 0, 1, FrameBlockID);
		blocks[1] = Block(0, 0, 2, FrameBlockID);
		blocks[2] = Block(0, 0, 3, SlotBarBlockID);
		blocks[3] = Block(0, 0, 4, FrameBlockID);

		blocks[4] = Block(0, -1, 1, FrameBlockID);
		blocks[5] = Block(0, -1, 2, FrameBlockID);
		blocks[6] = Block(0, -1, 3, SlotBarBlockID);
		blocks[7] = Block(0, -1, 4, FrameBlockID);

		blocks[8] = Block(0, 1, 1, FrameBlockID);
		blocks[9] = Block(0, 1, 2, SlotButtonBlockID);
		blocks[10] = Block(0, 1, 3, SlotBarBlockID);
		blocks[11] = Block(0, 1, 4, FrameBlockID);

		output = &blocks[1]; // this is where the rewards come out from
		break;
	}

}
