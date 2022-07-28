#include "GameAPI.h"
#include "SlotRoll.cpp"
#include "SlotMachine.cpp"
#include <string>
#include <vector>
#include <cmath> 



// Store slot machine blocks that generated structures
std::vector<CoordinateInBlocks> BlocksThatGenerated = {};


// Get offset values from view direction
// Used to correctly position structure depending on where the player looks
Offset GetOffset(DirectionVectorInCentimeters Direction) {
	int offsetX = 0;
	int offsetY = 0;

	if (std::abs(Direction.X) >= std::abs(Direction.Y) && Direction.X >= 0) { // Player looks at east
		offsetY = 1;
	}
	else if (std::abs(Direction.X) > std::abs(Direction.Y) && Direction.X < 0) { // Player looks at west
		offsetY = -1;
	}
	else if (std::abs(Direction.X) < std::abs(Direction.Y) && Direction.Y < 0) { // Player looks at south
		offsetX = -1;
	}
	else if (std::abs(Direction.X) <= std::abs(Direction.Y) && Direction.Y >= 0) { // Player looks at north
		offsetX = 1;
	}

	return Offset(offsetX, offsetY);
}

bool IsSafeToPlace(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {

	Offset offset = GetOffset(Direction);

	for (int i = 1; i <= 4; i++) {
		if (GetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i)).Type != EBlockType::Air) return false;
		if (GetBlock(At + CoordinateInBlocks(        0,         0, i)).Type != EBlockType::Air) return false;
		if (GetBlock(At + CoordinateInBlocks( offset.X,  offset.Y, i)).Type != EBlockType::Air) return false;
	}
	if (GetBlock(At + CoordinateInBlocks(-offset.X*2, offset.Y*2, 3)).Type != EBlockType::Air) return false;
	return true;
}

void PlaceSlotMachine(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
	/*
	Offset offset = GetOffset(Direction);

	// Create machine metal frame
	for (int i = 1; i <= 4; i++) {
		if (i == 3) continue;
		SetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i), FrameBlockID);
		SetBlock(At + CoordinateInBlocks(        0,         0, i), FrameBlockID);
		SetBlock(At + CoordinateInBlocks( offset.X,  offset.Y, i), FrameBlockID);
	}

	// Create activation button
	SetBlock(At + CoordinateInBlocks(-offset.X*2, offset.Y*2, 3), MetalButtonBlockID);
	*/
	SlotMachine::BuildHere(At, GetPlayerViewDirection());
}

void RemoveSlotMachine(CoordinateInBlocks At, DirectionVectorInCentimeters Direction) {
	Offset offset = GetOffset(Direction);

	for (int i = 1; i <= 4; i++) {
		SetBlock(At + CoordinateInBlocks(-offset.X, -offset.Y, i), EBlockType::Air);
		SetBlock(At + CoordinateInBlocks(0, 0, i), EBlockType::Air);
		SetBlock(At + CoordinateInBlocks(offset.X, offset.Y, i), EBlockType::Air);
	}
	SetBlock(At + CoordinateInBlocks(-offset.X * 2, offset.Y * 2, 3), EBlockType::Air);


}

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/



UniqueID ThisModUniqueIDs[] = { SlotMachineBlockID, FrameBlockID, SlotButtonBlockID,
								SlotZeroBlockID, SlotCherryBlockID, SlotBarBlockID, SlotBarBarBlockID, SlotBarBarBarBlockID, SlotSevenBlockID, SlotCrystalBlockID
								}; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 1;							 // Set how many times per second Event_Tick() is called. 0 means the Event_Tick() function is never called.
int TickNum = 1;							 // Tick counter. Used to skip ticks

/************************************************************* 
//	Functions (Run automatically by the game, you can put any code you want into them)
*************************************************************/

// Run every time a block is placed
void Event_BlockPlaced(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{

	if (CustomBlockID == SlotMachineBlockID) {
		//if (!IsSafeToPlace(At, GetPlayerViewDirection())) {
		if (!SlotMachine::EnoughSpace(At, GetPlayerViewDirection())) {
			SetBlock(At, EBlockType::Air);
			SpawnBlockItem(At, SlotMachineBlockID);
			SpawnHintText(At, L"Not enough space to place!", 3);
		}
		else {
			SlotMachine::BuildHere(At, GetPlayerViewDirection());
			BlocksThatGenerated.push_back(At);
		}
	}

}




// Run every time a block is destroyed
void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	if (CustomBlockID == SlotMachineBlockID) {
		std::vector<CoordinateInBlocks> temp = {};
		// Check if what we are trying to remove was indeed placed by this specific block
		for (CoordinateInBlocks coords : BlocksThatGenerated) {
			if (coords == At) {
				RemoveSlotMachine(At, GetPlayerViewDirection());
			}
			else {
				temp.push_back(coords); // This whole vector stuff could be expensive, consider iterators
			}
		}
		BlocksThatGenerated = temp;
	}
}


// Run every time a block is hit by a tool
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{
	if (CustomBlockID == SlotButtonBlockID) {
		SlotRoll roll = SlotRoll();
		std::wstring out(roll.dump.begin(), roll.dump.end());

		// Get offset to know which direction slot machine is facing
		Offset offset = SlotMachine::GetOutputOffset(At);

		SpawnHintText(At + CoordinateInBlocks(offset.X, offset.Y, 0), out, 3, 3);
		CoordinateInBlocks itemSpawn = (At + CoordinateInBlocks(offset.X, offset.Y, 0));

		// Spawn rewards based on the slots
		switch (roll.result) {
		case 0:
			SpawnBlockItem(itemSpawn, EBlockType::DryGrass);
			break;
		case 2:
			for (int i = 0; i < 3; i++)
				SpawnBlockItem(itemSpawn, EBlockType::Nugget_Coal);
			break;
		case 5:
			for (int i = 0; i < 3; i++)
				SpawnBlockItem(itemSpawn, EBlockType::Nugget_Copper);
			break;
		case 10:
			for (int i = 0; i < 3; i++)
				SpawnBlockItem(itemSpawn, EBlockType::IngotIron);
			break;
		case 25:
			for (int i = 0; i < 5; i++)
				SpawnBlockItem(itemSpawn, EBlockType::IngotIron);
			SpawnBlockItem(itemSpawn, EBlockType::Nugget_Gold);
			break;
		case 40:
			for (int i = 0; i < 10; i++)
				SpawnBlockItem(itemSpawn, EBlockType::IngotIron);
			SpawnBlockItem(itemSpawn, EBlockType::Crystal);
			break;
		case 80:
			for (int i = 0; i < 5; i++)
				SpawnBlockItem(itemSpawn, EBlockType::Nugget_Gold);
			SpawnBlockItem(itemSpawn, EBlockType::Crystal);
			break;
		case 100:
			for (int i = 0; i < 50; i++)
				SpawnBlockItem(itemSpawn, EBlockType::Crystal);
			break;
		}
	}
}

// Run X times per second, as specified in the TickRate variable at the top
void Event_Tick()
{
	
}



// Run once when the world is loaded
void Event_OnLoad(bool CreatedNewWorld)
{

}

// Run once when the world is exited
void Event_OnExit()
{
	
}

/*******************************************************

	Advanced functions

*******************************************************/


// Run every time any block is placed by the player
void Event_AnyBlockPlaced(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{
	SpawnHintText(At + up, GetPlayerViewDirection().ToString(), 5);
}

// Run every time any block is destroyed by the player
void Event_AnyBlockDestroyed(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{

}

// Run every time any block is hit by a tool
void Event_AnyBlockHitByTool(CoordinateInBlocks At, BlockInfo Type, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{

}


/*******************************************************

	For all the available game functions you can call, look at the GameAPI.h file

*******************************************************/