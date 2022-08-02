#include "SlotRoll.h"
#include "GameAPI.h"

int SlotRoll::GetRandom()
{
	return GetRandomInt<0, 100>();
}

SlotRoll::SlotRoll(bool test) {
	//srand(time(0));						// Uncomment this for unit tests
		// Let's roll slots!
	for (int i = 0; i < 3; i++) {
		int dice = GetRandom();
		dump += std::to_string(dice) + "\n";
		if (dice >= 1 && dice <= zero) {
			slots[i] = zero;
			dump += "this roll is zero\n";
		}
		else if (dice > zero && dice <= copper) {
			slots[i] = copper;
			dump += "this roll is copper\n";
		}
		else if (dice > copper && dice <= b) {
			slots[i] = b;
			dump += "this roll is b\n";
		}
		else if (dice > b && dice <= bb) {
			slots[i] = bb;
			dump += "this roll is bb\n";
		}
		else if (dice > bb && dice <= bbb) {
			slots[i] = bbb;
			dump += "this roll is bbb\n";
		}
		else if (dice > bbb && dice <= seven) {
			slots[i] = seven;
			dump += "this roll is seven\n";
		}
		else if (dice > seven && dice <= crystal) {
			slots[i] = crystal;
			dump += "this roll is crystal\n";
		}
	}

	result = 0;
	// Let's find out the result! (number of points)

	bool thrice = false;
	if (slots[0] == slots[1] && slots[1] == slots[2]) {
		thrice = true;
	}
	if (thrice) {				// All three slots are the same
		switch (slots[0]) {
		case crystal:
			result = 100;
			break;
		case seven:
			result = 80;
			break;
		case bbb:
			result = 40;
			break;
		case bb:
			result = 25;
			break;
		case b:
			result = 10;
			break;
		case copper:
			result = 10;
			break;
		case zero:
			result = 0;
			break;
		}
	}
	else {
		int barsNum = 0;					// All three slots are bars
		for (int i = 0; i < 3; i++) {
			if (slots[i] == b || slots[i] == bb || slots[i] == bbb) {
				barsNum++;
			}
		}
		if (barsNum == 3) {
			result = 5;
			dump += "all bars!\n";
		}
		else {
			int copperNum = 0;
			for (int i = 0; i < 3; i++) {
				if (slots[i] == copper) {   // There is 1 copper (cherry) or 2 coppers (cherries)
					copperNum++;
				}
			}
			if (copperNum == 2) {
				result = 5;
			}
			else if (copperNum == 1) {
				result = 2;
			}
			else {
				result = 0;
			}
		}
	}
}