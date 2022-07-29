#include "pch.h"
#include "CppUnitTest.h"
#include "../ProjectFiles/Source/SlotRoll.cpp"
#include "../ProjectFiles/Source/SlotMachineBlueprint.cpp"
#include "../ProjectFiles/Source/Block.cpp"
#include <iostream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{


	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(BlueprintIsFilledWithBlocks) {
			SlotMachineBlueprint bprint = SlotMachineBlueprint();
			Assert::AreEqual(12, bprint.size);

			Assert::IsTrue(bprint.blocks[0].info.IsValid());

			Assert::AreEqual(FrameBlockID, bprint.blocks[0].info.CustomBlockID);
			Assert::AreEqual(SlotBarBlockID, bprint.blocks[2].info.CustomBlockID);

			int64_t xcoord = 1;
			Assert::AreEqual(xcoord, bprint.blocks[5].coords.X);

			int64_t ycoord = 0;
			for (int i = 0; i < bprint.size; i++) {
				Assert::AreEqual(ycoord, bprint.blocks[i].coords.Y);
				Assert::IsTrue(bprint.blocks[i].info.IsValid());
			}

		}

		TEST_METHOD(SeeResultsOfRandomRoll) 
		// HEY!
		// Changes to SlotRoll::GetRandom() are needed for this test to work
		{

			/*
			SlotRoll roll = SlotRoll();

			// I hate c++ please send some help how do I just output an int into VS
			std::string tmp = std::to_string(roll.result);
			char const* ch = tmp.c_str();

			Logger::WriteMessage(roll.dump.c_str());
			Logger::WriteMessage(ch);
			*/
		}
	};
}
