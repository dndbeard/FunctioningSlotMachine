#include "GameAPI.h"
#include "Constants.cpp"
#include <vector>

/*************************************
*  Useful helper structures
*************************************/
enum Direction { north, south, west, east};

struct Offset {
	int X;
	int Y;
	int Z;
	Offset(int X, int Y) {
		this->X = X;
		this->Y = Y;
		this->Z = 0;
	}

	Offset(int X, int Y, int Z) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	// Get general direction the player is looking
	static Direction GetDirection(DirectionVectorInCentimeters Direction) {
		int offsetX = 0;
		int offsetY = 0;

		if (std::abs(Direction.X) >= std::abs(Direction.Y) && Direction.X >= 0) { // Player looks at east
			return east;
		}
		else if (std::abs(Direction.X) > std::abs(Direction.Y) && Direction.X < 0) { // Player looks at west
			return west;
		}
		else if (std::abs(Direction.X) < std::abs(Direction.Y) && Direction.Y < 0) { // Player looks at south
			return south;
		}
		else if (std::abs(Direction.X) <= std::abs(Direction.Y) && Direction.Y >= 0) { // Player looks at north
			return north;
		}

		return north;
	}
};

struct Block {
	BlockInfo info;
	CoordinateInBlocks coords;

	Block(BlockInfo info, CoordinateInBlocks coords) {
		this->info = info;
		this->coords = coords;
	}
};

/*****************************
* A static class that handles various calculations
* Can build and remove the Slot Machine, check if others are nearby, check for correct placement, calculate various offsets
* This class is made static and fully depends on the consistency of cyubeVR's world, without storing anything itself
******************************/
class SlotMachine {
public:

	static Direction ReverseDirection(Direction direction) {
		switch (direction) {
		case north:
			return south;
		case south:
			return north;
		case east:
			return west;
		case west:
			return east;
		}
	}

	// Blocks that Slot Machine is made of
	static constexpr UniqueID ConsistsOf [] = { FrameBlockID, SlotButtonBlockID, SlotMachineBlockID,
		SlotZeroBlockID, SlotCherryBlockID, SlotBarBlockID, SlotBarBarBlockID, SlotBarBarBarBlockID, SlotSevenBlockID, SlotCrystalBlockID
	};

	// Check if a block is among those that Slot Machine is made of
	static bool BlockInArray(UniqueID block, const UniqueID blockArray[]) {
		for (int i = 0; i < (sizeof(blockArray) / sizeof(*blockArray)); i++) {
			if (block == blockArray[i])
				return true;
		}
		return false;
	}

	// General offset for placing the Slot Machine
	// Used to generate and remove the Slot Machine
	static Offset GetOffset(DirectionVectorInCentimeters Direction) {
		return GetOffset(Offset::GetDirection(Direction));
	}

	static Offset GetOffset(Direction direction) {
		Offset offset = Offset(0, 0);
		switch (direction) {
		case north:
			offset.X = 1;
			break;
		case south:
			offset.X = -1;
			break;
		case west:
			offset.Y = -1;
			break;
		case east:
			offset.Y = 1;
			break;
		}
		return offset;
	}

	// Offset from a button (that was hit) to the block where rewards are spawned
	static Offset GetOutputOffset(DirectionVectorInCentimeters Direction) {
		Offset offset = Offset(0, 0);
		switch (Offset::GetDirection(Direction)) {
		case north:
			offset.Y = -1;
			offset.X = -1;
			break;
		case south:
			offset.Y = 1;
			offset.X = 1;
			break;
		case west:
			offset.X = 1;
			offset.Y = -1;
			break;
		case east:
			offset.X = -1;
			offset.Y = 1;
			break;
		}
		return offset;
	}


	// Check if there's enough space around origin block (SlotMachineBlock) to generate the Slot Machine
	static bool EnoughSpace(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
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
	static void BuildHere(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
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
	}

	// Remove the whole structure
	// At == origin block, Direction == where player is facing
	static void RemoveSlotMachine(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
		Offset offset = SlotMachine::GetOffset(SlotMachine::ReverseDirection(GetSlotMachineDirection(At)));

		for (int i = 1; i <= 4; i++) {
			SetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i), EBlockType::Air);
			SetBlock(At + CoordinateInBlocks(        0,         0, i), EBlockType::Air);
			SetBlock(At + CoordinateInBlocks( offset.X,  offset.Y, i), EBlockType::Air);
		}
	}



	// Search for a SlotButtonBlock from the origin point of SlotMachineBlock placed at "At" coordinates
	// (1, 0, 2) (0, 1, 2) (-1, 0, 2), (0, -1, 2)
	static CoordinateInBlocks GetButtonCoordinates(CoordinateInBlocks At) {
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
	static Direction GetSlotMachineDirection(CoordinateInBlocks At) {
		CoordinateInBlocks ButtonCoords = GetButtonCoordinates(At);
		if (ButtonCoords.X == 0 && ButtonCoords.Y == 1) return south;
		if (ButtonCoords.X == 0 && ButtonCoords.Y == -1) return north;
		if (ButtonCoords.X == 1 && ButtonCoords.Y == 0) return west;
		if (ButtonCoords.X == -1 && ButtonCoords.Y == 0) return east;
	}




};