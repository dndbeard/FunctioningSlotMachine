#pragma once
#include "GameAPI.h"

/**********************************
* This class combines coordinates and info into one entity
***********************************/
class Block {
public:
	// Info includes blocks EBlockType or UniqueID
	BlockInfo info;
	// X, Y, Z coordinates
	CoordinateInBlocks coords;

	// Empty constructor for inializing arrays
	Block();

	// Constructs a block from VoxelAPI entities
	Block(BlockInfo info, CoordinateInBlocks coords);

	// Constructs a block from numeric values
	// (X, Y, Z, UniqueID)
	Block(int X, int Y, int Z, int ID);

};