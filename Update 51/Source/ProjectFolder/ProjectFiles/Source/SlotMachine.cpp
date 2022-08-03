#include <vector>
#include <string>
#include "SlotMachine.h"


// Check if there's enough space around origin block (SlotMachineBlock) to generate the Slot Machine
bool SlotMachine::EnoughSpace(CoordinateInBlocks at, DirectionVectorInCentimeters direction) {

	Direction playerFacingDirection = DirectionHelper::GetDirection(direction);
	SlotMachineBlueprint bprint;
	// blueprint holds information on how to build Slot Machine
	try {
		bprint = SlotMachineBlueprint::getBlueprint(DirectionHelper::ReverseDirection(playerFacingDirection));
	}
	catch (std::exception& e) {
		Log(modName + L" did an oopsie!");
		return false;
	}

	// If any of the blocks is occupied, there is not enough space
	for (int i = 0; i < bprint.size; i++) {
		if (GetBlock(at + bprint.blocks[i].coords).Type != EBlockType::Air) return false;
	}

	// occupiedBlocks are coordinates that must be empty for a structure to be placed. They remain empty
	for (int i = 0; i < bprint.occupiedSize; i++) {
		if (GetBlock(at + bprint.occupiedBlocks[i].coords).Type != EBlockType::Air) return false;
	}

}

// Generate a Slot Machine from the origin block (SlotMachineBlock) at "At" coordinate
void SlotMachine::BuildHere(CoordinateInBlocks at, DirectionVectorInCentimeters direction) {

	Direction playerFacingDirection = DirectionHelper::GetDirection(direction);
	SlotMachineBlueprint bprint;
	// blueprint holds information on how to build Slot Machine
	try {
		bprint = SlotMachineBlueprint::getBlueprint(DirectionHelper::ReverseDirection(playerFacingDirection));
	}
	catch (std::exception& e) {
		Log(modName + L" did an oopsie!");
		return;
	}

	// Place blocks according to blueprint
	for (int i = 0; i < bprint.size; i++) {
		SetBlock(at + bprint.blocks[i].coords, bprint.blocks[i].info);
	}

}

// Remove the whole structure
// At == origin block
void SlotMachine::RemoveSlotMachine(CoordinateInBlocks at) {
	Direction machineFacingDirection = SlotMachine::GetSlotMachineDirection(at);

	// blueprint holds information on how to build Slot Machine
	SlotMachineBlueprint bprint;
	try {
		bprint = SlotMachineBlueprint::getBlueprint(machineFacingDirection);
	}
	catch (std::exception& e) {
		Log(modName + L" did an oopsie while trying to remove Slot Machine!");
		return;
	}

	for (int i = 0; i < bprint.size; i++) {
		if (GetBlock(at + bprint.blocks[i].coords).CustomBlockID != bprint.blocks[i].info.CustomBlockID) {
			return;
		}
	}

	// Remove blocks according to blueprint
	for (int i = 0; i < bprint.size; i++) {
		SetBlock(at + bprint.blocks[i].coords, EBlockType::Air);
	}

}


// Search for a SlotButtonBlock from the origin point of SlotMachineBlock placed at "At" coordinates
CoordinateInBlocks SlotMachine::GetButtonCoordinates(CoordinateInBlocks At) {

	for (int variant = 1; variant <= SlotMachineBlueprint::variantAmount; variant++) {
		SlotMachineBlueprint bprint;
		try {
			bprint = SlotMachineBlueprint::getBlueprint(variant);
		}
		catch (std::exception& e) {
			Log(modName + L" did an oopsie!");
			throw e;
		}
		if (GetBlock(At + bprint.button->coords).CustomBlockID == SlotButtonBlockID) {
			return bprint.button->coords;
		}
	}

	throw std::invalid_argument("Button was not found! The structure is probably missing or invalid.");
}


	
// Get a general direction a generated Slot Machine is facing
// CAREFUL!!! This direction is  OPPOSITE of where player's view is directed when generating a Slot Machine
Direction SlotMachine::GetSlotMachineDirection(CoordinateInBlocks At) {
	CoordinateInBlocks ButtonCoords = GetButtonCoordinates(At);
	if (ButtonCoords.X == 0 && ButtonCoords.Y == 1) return Direction::south;
	if (ButtonCoords.X == 0 && ButtonCoords.Y == -1) return Direction::north;
	if (ButtonCoords.X == 1 && ButtonCoords.Y == 0) return Direction::east;
	if (ButtonCoords.X == -1 && ButtonCoords.Y == 0) return Direction::west;
}


std::pair<CoordinateInBlocks, SlotMachineBlueprint> SlotMachine::GetBlueprintVariantFromButton(CoordinateInBlocks At)
{
	for (int variant = 1; variant <= SlotMachineBlueprint::variantAmount; variant++) {
		SlotMachineBlueprint bprint;
		try {
			bprint = SlotMachineBlueprint::getBlueprint(variant);
		}
		catch (std::exception& e) {
			Log(modName + L" did an oopsie!");
			throw e;
		}
		CoordinateInBlocks offsetToOrigin = CoordinateInBlocks(
			-bprint.button->coords.X,
			-bprint.button->coords.Y,
			-bprint.button->coords.Z
		);

		if (GetBlock(At + offsetToOrigin).CustomBlockID == SlotMachineBlockID) {
			return std::make_pair(At + offsetToOrigin, bprint);
		}
	}
}

bool SlotMachine::IsSlot(UniqueID ID) {
	return ID == SlotBarBarBarBlockID ||
		ID == SlotBarBarBlockID ||
		ID == SlotBarBlockID ||
		ID == SlotCherryBlockID ||
		ID == SlotCrystalBlockID ||
		ID == SlotSevenBlockID ||
		ID == SlotZeroBlockID
		;
}


void SlotMachine::LetsRoll(CoordinateInBlocks buttonCoordinates) {
	CoordinateInBlocks originBlockCoordinate;
	SlotMachineBlueprint bprint;

	std::pair pairOfValues = GetBlueprintVariantFromButton(buttonCoordinates);
	originBlockCoordinate = pairOfValues.first;
	bprint = pairOfValues.second;

	for (int i = 0; i < bprint.size; i++) {
		if (IsSlot(bprint.blocks[i].info.CustomBlockID)) {
			SetBlock(bprint.blocks[i].coords, SlotAnimatedBlockID);
		}
	}


}

