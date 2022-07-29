#include "Block.h"

Block::Block() {
	this->info = BlockInfo(0);
	this->coords = CoordinateInBlocks(0, 0, 0);
}

Block::Block(BlockInfo info, CoordinateInBlocks coords) {
	this->info = info;
	this->coords = coords;
}

Block::Block(int X, int Y, int Z, int ID) {
	this->info = BlockInfo(ID);
	this->coords = CoordinateInBlocks(X, Y, Z);
}