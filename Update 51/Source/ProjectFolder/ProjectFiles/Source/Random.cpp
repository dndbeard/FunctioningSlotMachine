#include "GameAPI.h"

class Random {
	public:
	static int GetRandom() {
		return GetRandomInt<0, 100>();
	}
};