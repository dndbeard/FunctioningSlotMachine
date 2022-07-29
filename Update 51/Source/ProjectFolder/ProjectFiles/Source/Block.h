#pragma once
#include "GameAPI.h"

class Block {
public:
	BlockInfo info;
	CoordinateInBlocks coords;

	Block();

	Block(BlockInfo info, CoordinateInBlocks coords);

	Block(int X, int Y, int Z, int ID);

};