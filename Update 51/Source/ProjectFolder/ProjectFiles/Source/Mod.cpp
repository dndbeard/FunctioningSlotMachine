#include "SlotRoll.h"
#include "SlotMachine.h"
#include <cmath> 

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/



UniqueID ThisModUniqueIDs[] = { SlotMachineBlockID, FrameBlockID, SlotButtonBlockID,
								SlotZeroBlockID, SlotCherryBlockID, SlotBarBlockID, SlotBarBarBlockID, SlotBarBarBarBlockID, SlotSevenBlockID, SlotCrystalBlockID,
								SlotAnimatedBlockID
}; // All the UniqueIDs this mod manages. Functions like Event_BlockPlaced are only called for blocks of IDs mentioned here. 

float TickRate = 1;							 // Set how many times per second Event_Tick() is called. 0 means the Event_Tick() function is never called.
int test = GetRandomInt<0, 100>();			 // DON'T REMOVE THIS! 

/*************************************************************
//	Functions (Run automatically by the game, you can put any code you want into them)
*************************************************************/

// Run every time a block is placed
void Event_BlockPlaced(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{

	if (CustomBlockID == SlotMachineBlockID) {

		if (!SlotMachine::EnoughSpace(At, GetPlayerViewDirection())) {				// Check if there is enough space to place Slot Machine
			SetBlock(At, EBlockType::Air);									// If not, remove placed block, spawn block item and spawn hint
			SpawnBlockItem(At, SlotMachineBlockID);
			SpawnHintText(At, L"Not enough space to place!", 3);
		}
		else {
			SlotMachine::BuildHere(At, GetPlayerViewDirection());					// If yes, build the structure around origin block
		}
	}

}


// Run every time a block is destroyed
void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	if (CustomBlockID == SlotMachineBlockID) {
		try {
			SlotMachine::RemoveSlotMachine(At);
		}
		catch (std::exception& e) {
			Log(modName + L" did an oopsie while destroying SlotMachineBlock!");
		}
	}

}


// Run every time a block is hit by a tool
void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{
	if (CustomBlockID == SlotButtonBlockID) {
		SlotRoll roll = SlotRoll();
		std::wstring out(roll.dump.begin(), roll.dump.end());

		// Get offset to know which direction slot machine is facing
		/*
		Offset offset = SlotMachine::GetOutputOffset(GetPlayerViewDirection());

		SpawnHintText(At + CoordinateInBlocks(offset.X, offset.Y, 0), out, 3, 3);
		CoordinateInBlocks itemSpawn = (At + CoordinateInBlocks(offset.X, offset.Y, 0));
		*/
		CoordinateInBlocks itemSpawn = At +									// coordinates where we'll spawn items
			SlotMachineBlueprint::getBlueprint(								// blueprint varian of the machine			
				Offset::ReverseDirection(								// direction of slot machine
					Offset::GetDirection(GetPlayerViewDirection())			// direction of player view
					)
				)
					.outputRelativeToButton;								// offset in coordinates

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