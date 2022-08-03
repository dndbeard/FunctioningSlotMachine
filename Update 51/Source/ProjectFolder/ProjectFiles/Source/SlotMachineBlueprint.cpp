#include "SlotMachineBlueprint.h"

static const SlotMachineBlueprint northDirectedMachineBlueprint = SlotMachineBlueprint(1);
static const SlotMachineBlueprint southDirectedMachineBlueprint = SlotMachineBlueprint(2);
static const SlotMachineBlueprint westDirectedMachineBlueprint = SlotMachineBlueprint(3);
static const SlotMachineBlueprint eastDirectedMachineBlueprint = SlotMachineBlueprint(4);

static const SlotMachineBlueprint allBlueprints[4] = { northDirectedMachineBlueprint, southDirectedMachineBlueprint, westDirectedMachineBlueprint, eastDirectedMachineBlueprint };

SlotMachineBlueprint SlotMachineBlueprint::getBlueprint(int x) {
	switch (x) {
	case 1:
		return northDirectedMachineBlueprint;
	case 2:
		return southDirectedMachineBlueprint;
	case 3:
		return westDirectedMachineBlueprint;
	case 4:
		return eastDirectedMachineBlueprint;
	default:
		throw std::invalid_argument("getBlueprint's only argument should be in range of 1-4! 1 for north, 2 for south, 3 for east, 4 for west");
	}
}

SlotMachineBlueprint::SlotMachineBlueprint() {
	blocks[0] = Block(0, 0, 1, FrameBlockID);
	blocks[1] = Block(0, 0, 2, FrameBlockID);
	blocks[2] = Block(0, 0, 3, SlotBarBlockID);
	blocks[3] = Block(0, 0, 4, FrameBlockID);

	blocks[4] = Block(0, -1, 1, FrameBlockID);
	blocks[5] = Block(0, -1, 2, SlotButtonBlockID);
	blocks[6] = Block(0, -1, 3, SlotBarBlockID);
	blocks[7] = Block(0, -1, 4, FrameBlockID);

	blocks[8] = Block(0, 1, 1, FrameBlockID);
	blocks[9] = Block(0, 1, 2, FrameBlockID);
	blocks[10] = Block(0, 1, 3, SlotBarBlockID);
	blocks[11] = Block(0, 1, 4, FrameBlockID);

	output = &blocks[1]; // this is where the rewards come out from
	button = &blocks[5];
}

SlotMachineBlueprint::SlotMachineBlueprint(int x) {
	switch (x) { // Direction THE MACHINE is facing
	case 1: // north
		blocks[0] = Block(0, 0, 1, FrameBlockID);
		blocks[1] = Block(0, 0, 2, FrameBlockID);
		blocks[2] = Block(0, 0, 3, SlotBarBlockID);
		blocks[3] = Block(0, 0, 4, FrameBlockID);

		blocks[4] = Block(0, -1, 1, FrameBlockID);
		blocks[5] = Block(0, -1, 2, SlotButtonBlockID);
		blocks[6] = Block(0, -1, 3, SlotBarBlockID);
		blocks[7] = Block(0, -1, 4, FrameBlockID);

		blocks[8] = Block(0, 1, 1, FrameBlockID);
		blocks[9] = Block(0, 1, 2, FrameBlockID);
		blocks[10] = Block(0, 1, 3, SlotBarBlockID);
		blocks[11] = Block(0, 1, 4, FrameBlockID);

		output = &blocks[1]; // this is where the rewards come out from
		button = &blocks[5];
		break;
	case 2: // south
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
		button = &blocks[9];
		break;
	case 3: // west
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
		button = &blocks[9];
		break;
	case 4: // east
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

		output = &blocks[1]; // this is where the rewards come out from
		button = &blocks[5];
		break;
	}

}
