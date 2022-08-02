#include <vector>
#include <string>
#include "SlotMachine.h"

Direction SlotMachine::ReverseDirection(Direction direction) {
	switch (direction) {
	case Direction::north:
		return Direction::south;
	case Direction::south:
		return Direction::north;
	case Direction::east:
		return Direction::west;
	case Direction::west:
		return Direction::east;
	}
}

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
		offset.X = -1;
		break;
	case Direction::south:
		offset.Y = 1;
		offset.X = 1;
		break;
	case Direction::west:
		offset.X = 1;
		offset.Y = -1;
		break;
	case Direction::east:
		offset.X = -1;
		offset.Y = 1;
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
void SlotMachine::BuildHere(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
	SlotMachineBlueprint bprint = SlotMachineBlueprint();
	//SpawnHintText(At + up, std::to_wstring(bprint.size), 3);
	for (int i = 0; i < bprint.size; i++) {
		SetBlock(At + bprint.blocks[i].coords, bprint.blocks[i].info);
		//SpawnHintText(At + up, std::to_wstring(i), 3);
	}
	/*
	Offset offset = GetOffset(Direction);
	for (int i = 1; i <= 4; i++) {
		if (i == 3) {  // Set the slots
			SetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i), SlotAnimatedBlockID);
			SetBlock(At + CoordinateInBlocks(        0,         0, i), SlotAnimatedBlockID);
			SetBlock(At + CoordinateInBlocks( offset.X,  offset.Y, i), SlotAnimatedBlockID);
		}
		else {			// Set the frame
			SetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i), FrameBlockID);
			SetBlock(At + CoordinateInBlocks(        0,         0, i), FrameBlockID);
			SetBlock(At + CoordinateInBlocks( offset.X,  offset.Y, i), FrameBlockID);
		}
	}
	// Set the button
	SetBlock(At + CoordinateInBlocks(-offset.X, offset.Y, 2), SlotButtonBlockID);
	*/
}

// Remove the whole structure
// At == origin block, Direction == where player is facing
void SlotMachine::RemoveSlotMachine(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
	SlotMachineBlueprint bprint = SlotMachineBlueprint();
	for (int i = 0; i < bprint.size; i++) {
		SetBlock(At + bprint.blocks[i].coords, EBlockType::Air);
		//SpawnHintText(At + up, std::to_wstring(i), 3);
	}
	/*
	Offset offset = SlotMachine::GetOffset(SlotMachine::ReverseDirection(GetSlotMachineDirection(At)));
		for (int i = 1; i <= 4; i++) {
		SetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i), EBlockType::Air); // 1, 0, i
		SetBlock(At + CoordinateInBlocks(        0,         0, i), EBlockType::Air); 
		SetBlock(At + CoordinateInBlocks( offset.X,  offset.Y, i), EBlockType::Air); // -1, 0, i
	}
	*/
}



// Search for a SlotButtonBlock from the origin point of SlotMachineBlock placed at "At" coordinates
// (1, 0, 2) (0, 1, 2) (-1, 0, 2), (0, -1, 2)
CoordinateInBlocks SlotMachine::GetButtonCoordinates(CoordinateInBlocks At) {
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

	return CoordinateInBlocks(0, 0, 0);
}
	
// Get a general direction a generated Slot Machine is facing
// CAREFUL!!! This direction is  OPPOSITE of where player's view is directed when generating a Slot Machine
Direction SlotMachine::GetSlotMachineDirection(CoordinateInBlocks At) {
	CoordinateInBlocks ButtonCoords = GetButtonCoordinates(At);
	if (ButtonCoords.X == 0 && ButtonCoords.Y == 1) return Direction::south;
	if (ButtonCoords.X == 0 && ButtonCoords.Y == -1) return Direction::north;
	if (ButtonCoords.X == 1 && ButtonCoords.Y == 0) return Direction::west;
	if (ButtonCoords.X == -1 && ButtonCoords.Y == 0) return Direction::east;
}
