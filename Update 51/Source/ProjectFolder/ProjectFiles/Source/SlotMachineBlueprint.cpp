#include "SlotMachineBlueprint.h"

// Create all variations once and store them here
static const SlotMachineBlueprint northDirectedMachineBlueprint = SlotMachineBlueprint(1);
static const SlotMachineBlueprint southDirectedMachineBlueprint = SlotMachineBlueprint(2);
static const SlotMachineBlueprint westDirectedMachineBlueprint = SlotMachineBlueprint(3);
static const SlotMachineBlueprint eastDirectedMachineBlueprint = SlotMachineBlueprint(4);


SlotMachineBlueprint SlotMachineBlueprint::getBlueprint(int variant) {
	switch (variant) {
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
	SlotMachineBlueprint(1);
}

SlotMachineBlueprint::SlotMachineBlueprint(int variant) {
	switch (variant) { // Direction THE MACHINE is facing
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

		button = &blocks[5];

		occupiedBlocks[0] = Block(0, 1, 2, SlotButtonBlockID);
		occupiedBlocks[1] = Block(1, 0, 2, SlotButtonBlockID);
		occupiedBlocks[2] = Block(-1, 0, 2, SlotButtonBlockID);

		occupiedBlocks[3] = Block(0, 2, 0, SlotMachineBlockID);
		occupiedBlocks[4] = Block(0, -2, 0, SlotMachineBlockID);
		occupiedBlocks[5] = Block(2, 0, 0, SlotMachineBlockID);
		occupiedBlocks[6] = Block(-2, 0, 0, SlotMachineBlockID);


		outputRelativeToButton = CoordinateInBlocks(1, 1, 0);
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

		button = &blocks[9];

		occupiedBlocks[0] = Block(0, -1, 2, SlotButtonBlockID);
		occupiedBlocks[1] = Block(1, 0, 2, SlotButtonBlockID);
		occupiedBlocks[2] = Block(-1, 0, 2, SlotButtonBlockID);

		occupiedBlocks[3] = Block(0, 2, 0, SlotMachineBlockID);
		occupiedBlocks[4] = Block(0, -2, 0, SlotMachineBlockID);
		occupiedBlocks[5] = Block(2, 0, 0, SlotMachineBlockID);
		occupiedBlocks[6] = Block(-2, 0, 0, SlotMachineBlockID);

		outputRelativeToButton = CoordinateInBlocks(-1, -1, 0);
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

		button = &blocks[9];

		occupiedBlocks[0] = Block(0, 1, 2, SlotButtonBlockID);
		occupiedBlocks[1] = Block(1, 0, 2, SlotButtonBlockID);
		occupiedBlocks[2] = Block(0, -1, 2, SlotButtonBlockID);

		occupiedBlocks[3] = Block(0, 2, 0, SlotMachineBlockID);
		occupiedBlocks[4] = Block(0, -2, 0, SlotMachineBlockID);
		occupiedBlocks[5] = Block(2, 0, 0, SlotMachineBlockID);
		occupiedBlocks[6] = Block(-2, 0, 0, SlotMachineBlockID);

		outputRelativeToButton = CoordinateInBlocks(1, -1, 0);
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

		button = &blocks[5];

		occupiedBlocks[0] = Block(0, 1, 2, SlotButtonBlockID);
		occupiedBlocks[1] = Block(0, -1, 2, SlotButtonBlockID);
		occupiedBlocks[2] = Block(-1, 0, 2, SlotButtonBlockID);

		occupiedBlocks[3] = Block(0, 2, 0, SlotMachineBlockID);
		occupiedBlocks[4] = Block(0, -2, 0, SlotMachineBlockID);
		occupiedBlocks[5] = Block(2, 0, 0, SlotMachineBlockID);
		occupiedBlocks[6] = Block(-2, 0, 0, SlotMachineBlockID);

		outputRelativeToButton = CoordinateInBlocks(-1, 1, 0);

		break;

	default:
		throw std::exception("Invalid number of blueprint variation! Can only be between 1 and 4");
	}


}
