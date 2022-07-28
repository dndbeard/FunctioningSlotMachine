#include "pch.h"
#include "CppUnitTest.h"
#include "../ProjectFiles/Source/SlotRoll.cpp"
#include <iostream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{


	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1) 
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
