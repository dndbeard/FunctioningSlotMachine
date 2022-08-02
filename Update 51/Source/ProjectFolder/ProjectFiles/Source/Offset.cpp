#include "GameAPI.h"

enum class Direction { north, south, west, east };


class Offset {
public:
	// 3D coordinates
	int X;
	int Y;
	int Z;

	// Construct from 2 coordinates
	Offset(int X, int Y) {
		this->X = X;
		this->Y = Y;
		this->Z = 0;
	}

	// Construct from 3 coordinates
	Offset(int X, int Y, int Z) {
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	// Convert Direction into wstring
	static std::wstring DirectionToString(Direction direction) {
		switch (direction) {
		case Direction::north:
			return L"north";
		case Direction::south:
			return L"south";
		case Direction::west:
			return L"west";
		case Direction::east:
			return L"east";
		}
	}

	// Get general direction the player is looking
	static Direction GetDirection(DirectionVectorInCentimeters Direction) {
		int offsetX = 0;
		int offsetY = 0;

		if (std::abs(Direction.X) >= std::abs(Direction.Y) && Direction.X >= 0) { // Player looks at east
			return Direction::east;
		}
		else if (std::abs(Direction.X) > std::abs(Direction.Y) && Direction.X < 0) { // Player looks at west
			return Direction::west;
		}
		else if (std::abs(Direction.X) < std::abs(Direction.Y) && Direction.Y < 0) { // Player looks at south
			return Direction::south;
		}
		else if (std::abs(Direction.X) <= std::abs(Direction.Y) && Direction.Y >= 0) { // Player looks at north
			return Direction::north;
		}
		return Direction::north;
	}

	// Get the opposite of the given direction
	Direction ReverseDirection(Direction direction) {
		switch (direction) {
		case Direction::north:
			return Direction::south;
		case Direction::south:
			return Direction::north;
		case Direction::east:
			return Direction::west;
		case Direction::west:
			return Direction::east;
		}
	}

};
