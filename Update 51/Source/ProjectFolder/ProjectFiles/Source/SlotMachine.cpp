#include <vector>
#include <string>
#include "SlotMachine.h"

// Check if a block is among those that Slot Machine is made of
bool SlotMachine::BlockInArray(UniqueID block, const UniqueID blockArray[]) {
	for (int i = 0; i < (sizeof(blockArray) / sizeof(*blockArray)); i++) {
		if (block == blockArray[i])
			return true;
	}
	return false;
}

// General offset for placing the Slot Machine
// Used to generate and remove the Slot Machine
Offset SlotMachine::GetOffset(DirectionVectorInCentimeters Direction) {
	return GetOffset(Offset::GetDirection(Direction));
}

Offset SlotMachine::GetOffset(Direction direction) {
	Offset offset = Offset(0, 0);
	switch (direction) {
	case Direction::north:
		offset.X = 1;
		break;
	case Direction::south:
		offset.X = -1;
		break;
	case Direction::west:
		offset.Y = -1;
		break;
	case Direction::east:
		offset.Y = 1;
		break;
	}
	return offset;
}

// Offset from a button (that was hit) to the block where rewards are spawned
Offset SlotMachine::GetOutputOffset(DirectionVectorInCentimeters Direction) {
	Offset offset = Offset(0, 0);
	switch (Offset::GetDirection(Direction)) {
	case Direction::north:
		offset.Y = -1;
		offset.X = 1;
		break;
	case Direction::south:
		offset.Y = 1;
		offset.X = -1;
		break;
	case Direction::west:
		offset.X = 1;
		offset.Y = 1;
		break;
	case Direction::east:
		offset.X = -1;
		offset.Y = -1;
		break;
	}
	return offset;
}


// Check if there's enough space around origin block (SlotMachineBlock) to generate the Slot Machine
bool SlotMachine::EnoughSpace(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
	Offset offset = SlotMachine::GetOffset(Direction);

	// Check the space that will be occupied
	for (int i = 1; i <= 4; i++) {
		if (GetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i)).Type != EBlockType::Air) return false;
		if (GetBlock(At + CoordinateInBlocks(0, 0, i)).Type != EBlockType::Air) return false;
		if (GetBlock(At + CoordinateInBlocks(offset.X, offset.Y, i)).Type != EBlockType::Air) return false;
	}

	// Check the space nearby: no two slot machines back to back! For reasons, just trust me
	for (int i = 1; i <= 4; i++) {
		if (BlockInArray(GetBlock(At + CoordinateInBlocks(offset.Y, offset.X, i)).CustomBlockID, ConsistsOf)) {
			return false;
		}
		if (BlockInArray(GetBlock(At + CoordinateInBlocks(-offset.Y, -offset.X, i)).CustomBlockID, ConsistsOf)) {
			return false;
		}
	}
	return true;
}

// Generate a Slot Machine from the origin block (SlotMachineBlock) at "At" coordinate
void SlotMachine::BuildHere(CoordinateInBlocks at, DirectionVectorInCentimeters direction) {

	Direction playerFacingDirection = Offset::GetDirection(direction);
	SlotMachineBlueprint bprint;
	// blueprint holds information on how to build Slot Machine
	try {
		bprint = SlotMachineBlueprint::getBlueprint(Offset::ReverseDirection(playerFacingDirection));
	}
	catch (std::exception& e) {
		Log(modName + L" did an oopsie!");
		return;
	}
	for (int i = 0; i < bprint.size; i++) {
		SetBlock(at + bprint.blocks[i].coords, bprint.blocks[i].info);

	}

}

// Remove the whole structure
// At == origin block, Direction == where player is facing
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
		SetBlock(at + bprint.blocks[i].coords, EBlockType::Air);
	}

}


// Search for a SlotButtonBlock from the origin point of SlotMachineBlock placed at "At" coordinates
CoordinateInBlocks SlotMachine::GetButtonCoordinates(CoordinateInBlocks At) {

	for (int i = 1; i <= SlotMachineBlueprint::blueprintAmount; i++) {
		SlotMachineBlueprint bprint;
		try {
			bprint = SlotMachineBlueprint::getBlueprint(i);
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

	/*
	CoordinateInBlocks coords = At + CoordinateInBlocks(1, 0, 2);
	BlockInfo found = GetBlock(coords);
	if (found.CustomBlockID == SlotButtonBlockID){
		return coords;
	}

	coords = At + CoordinateInBlocks(-1, 0, 2);
	found = GetBlock(coords);
	if (found.CustomBlockID == SlotButtonBlockID) {
		return coords;
	}

	coords = At + CoordinateInBlocks(0, 1, 2);
	found = GetBlock(coords);
	if (found.CustomBlockID == SlotButtonBlockID) {
		return coords;
	}
	coords = At + CoordinateInBlocks(0, -1, 2);
	found = GetBlock(coords);
	if (found.CustomBlockID == SlotButtonBlockID) {
		return coords;
	}

	throw std::invalid_argument("No button found near this origin block!");
	*/
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
