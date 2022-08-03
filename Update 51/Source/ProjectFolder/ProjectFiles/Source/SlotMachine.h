#pragma once
#include <vector>
#include <string>
#include "SlotMachineBlueprint.h"
#include "Offset.cpp"


/*****************************
* A static class that handles various calculations
* Can build and remove the Slot Machine, check if others are nearby, check for correct placement, calculate various offsets
* This class is made static and fully depends on the consistency of cyubeVR's world, without storing anything itself
******************************/
#include "SlotMachineBlueprint.h"

class SlotMachine {
public:

	static Direction ReverseDirection(Direction direction);

	// Blocks that Slot Machine is made of
	static constexpr UniqueID ConsistsOf[] = { FrameBlockID, SlotButtonBlockID, SlotMachineBlockID,
		SlotZeroBlockID, SlotCherryBlockID, SlotBarBlockID, SlotBarBarBlockID, SlotBarBarBarBlockID, SlotSevenBlockID, SlotCrystalBlockID
	};

	// Check if a block is among those that Slot Machine is made of
	static bool BlockInArray(UniqueID block, const UniqueID blockArray[]);

	// General offset for placing the Slot Machine
	// Used to generate and remove the Slot Machine
	static Offset GetOffset(DirectionVectorInCentimeters Direction);

	static Offset GetOffset(Direction direction);

	// Offset from a button (that was hit) to the block where rewards are spawned
	static Offset GetOutputOffset(DirectionVectorInCentimeters Direction);

	// Check if there's enough space around origin block (SlotMachineBlock) to generate the Slot Machine
	static bool EnoughSpace(CoordinateInBlocks At, DirectionVectorInCentimeters Direction);

	// Generate a Slot Machine from the origin block (SlotMachineBlock) at "At" coordinate
	static void BuildHere(CoordinateInBlocks At, DirectionVectorInCentimeters Direction);

	// Remove the whole structure
	// At == origin block
	static void RemoveSlotMachine(CoordinateInBlocks At);


	// Search for a SlotButtonBlock from the origin point of SlotMachineBlock placed at "At" coordinates
	// (1, 0, 2) (0, 1, 2) (-1, 0, 2), (0, -1, 2)
	static CoordinateInBlocks GetButtonCoordinates(CoordinateInBlocks At);

	// Get a general direction a generated Slot Machine is facing
	// CAREFUL!!! This direction is  OPPOSITE of where player's view is directed when generating a Slot Machine
	static Direction GetSlotMachineDirection(CoordinateInBlocks At);


};