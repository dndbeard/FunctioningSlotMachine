#pragma once
#include <vector>
#include <string>
#include "SlotMachineBlueprint.h"
#include "Direction.cpp"
#include "SlotRoll.h"


/*****************************
* A static class that handles various calculations
* Can build and remove the Slot Machine, check if others are nearby, check for correct placement, calculate various offsets
* This class is made static and fully depends on the consistency of cyubeVR's world, without storing anything itself
******************************/
#include "SlotMachineBlueprint.h"

class SlotMachine {
public:

	// Blocks that Slot Machine is made of
	static constexpr UniqueID ConsistsOf[] = { FrameBlockID, SlotButtonBlockID, SlotMachineBlockID,
		SlotZeroBlockID, SlotCherryBlockID, SlotBarBlockID, SlotBarBarBlockID, SlotBarBarBarBlockID, SlotSevenBlockID, SlotCrystalBlockID
	};

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

	static void LetsRoll(CoordinateInBlocks buttonCoordinates);

	static void SetSlotsFromSlotRoll(SlotRoll slotRoll, CoordinateInBlocks buttonCoordinate);

	static UniqueID GetSlotBlockID(Slot slot);

	// Given coordinates of SlotButtonBlock, figure out the variant of Slot Machine
	static std::pair<CoordinateInBlocks, SlotMachineBlueprint> GetBlueprintVariantFromButton(CoordinateInBlocks At);

	// Check if block is one of the slots (cherry, seven, bars, etc.)
	static bool IsSlot(UniqueID ID);

	// Get a general direction a generated Slot Machine is facing
	// CAREFUL!!! This direction is  OPPOSITE of where player's view is directed when generating a Slot Machine
	static Direction GetSlotMachineDirection(CoordinateInBlocks At);


};