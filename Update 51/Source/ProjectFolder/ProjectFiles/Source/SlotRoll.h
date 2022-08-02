#pragma once
#include <string>


// You can adjust probabilities here
enum Slot {
	zero = 30,
	copper = zero + 20,
	b = copper + 16,
	bb = b + 13,
	bbb = bb + 9,
	seven = bbb + 7,
	crystal = seven + 5
};


class SlotRoll {
public:
	Slot slots[3];
	int result;								// Number of points that depends on combination of slots
	std::string dump = "";					// Output for testing

	int GetRandom();

	SlotRoll(bool test = false);
};