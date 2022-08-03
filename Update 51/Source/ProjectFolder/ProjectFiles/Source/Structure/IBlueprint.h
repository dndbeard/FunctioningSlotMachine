#pragma once
#include "../Block.h"

// Blueprint interface (abstract class)
class IBlueprint {
public:
	static const int size;				  // this structure consists of 12 blocks, excluding the origin block
	static const int blueprintAmount;	  // how many variations of blueprint there are (for example 4 for different directions)

	static Block blocks[];			      // array that holds info about blocks inside structure

	virtual ~IBlueprint() {};
	IBlueprint();						  // default constructor
	IBlueprint(int x);     				  // construct one of the blueprint variants

	virtual IBlueprint getBlueprint(int x) = 0; // get one of the variants
};